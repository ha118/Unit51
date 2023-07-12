// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolEnemyController.h"
#include "PatrolEnemy.h"
#include "AIPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

void APatrolEnemyController::OnPossess(APawn* EnemyPawn)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Starting possess"));
	APatrolEnemy* PatrolEnemy = Cast<APatrolEnemy>(EnemyPawn);
	if (PatrolEnemy) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Possessed"));
		if (PatrolEnemy->BehaviorTree->BlackboardAsset) {
			BlackboardComp->InitializeBlackboard(*(PatrolEnemy->BehaviorTree->BlackboardAsset));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Blackboard init"));
		}
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), PatrolPoints);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("starting tree"));
		BehaviorComp->StartTree(*PatrolEnemy->BehaviorTree);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Unable to possess"));
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
}

void APatrolEnemyController::setPlayerCaught(APawn* EnemyPawn)
{
	if (BlackboardComp) {
		BlackboardComp->SetValueAsObject(PlayerKey, EnemyPawn);
	}
}
