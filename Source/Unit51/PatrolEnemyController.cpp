// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolEnemyController.h"
#include "PatrolEnemy.h"
#include "AIPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"

void APatrolEnemyController::OnPerception(AActor* EnemyPawn, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("On perception called"));

	if (BlackboardComp) {
		FString msg = FString::Printf(TEXT("Enemy Pawn is %s"), *GetNameSafe(EnemyPawn));
		BlackboardComp->SetValueAsObject(PlayerKey, Stimulus.WasSuccessfullySensed() ? EnemyPawn : nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, msg);
	}
}

void APatrolEnemyController::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);
	APatrolEnemy* PatrolEnemy = Cast<APatrolEnemy>(PossessedPawn);

	// Call OnPerception on perception updated
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &APatrolEnemyController::OnPerception);

	if (PatrolEnemy) {
		if (PatrolEnemy->BehaviorTree->BlackboardAsset) {
			BlackboardComp->InitializeBlackboard(*(PatrolEnemy->BehaviorTree->BlackboardAsset));
		}
		// Getting all patrol points in world
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), PatrolPoints);

		BehaviorComp->StartTree(*PatrolEnemy->BehaviorTree);
	}

}

APatrolEnemyController::APatrolEnemyController()
{
	/*Initialize blackboard and bahevior tree*/
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	/*Initialize blackboar keys*/
	PlayerKey = "Target";
	TargetLocation = "LocationToGo";
	CurrentPatrolPoint = 0;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));

	// Create Sight Sense
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	Sight->SightRadius = 2000.f;
	Sight->LoseSightRadius = Sight->SightRadius + 500.f;
	Sight->PeripheralVisionAngleDegrees = 90.0f;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	// Register Sight Sense to AIPerceptionComponent;
	AIPerceptionComponent->ConfigureSense(*Sight);
	AIPerceptionComponent->SetDominantSense(Sight->GetSenseImplementation());
}
