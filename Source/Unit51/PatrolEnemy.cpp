// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolEnemy.h"
#include "PatrolEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
APatrolEnemy::APatrolEnemy()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

}

// Called when the game starts or when spawned
void APatrolEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (PawnSensingComp) {
		PawnSensingComp->OnSeePawn.AddDynamic(this, &APatrolEnemy::OnPlayerCaught);
	}
	
}

// Called to bind functionality to input
void APatrolEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APatrolEnemy::OnPlayerCaught(APawn* Pawn)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You have been caught"));
	APatrolEnemyController* PatrolEnemyController = Cast<APatrolEnemyController>(GetController());
	if (PatrolEnemyController) {
		PatrolEnemyController->setPlayerCaught(Pawn);
	}

}

