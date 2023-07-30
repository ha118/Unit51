// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolEnemy.h"
#include "PatrolEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
APatrolEnemy::APatrolEnemy()
{

}

// Called when the game starts or when spawned
void APatrolEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void APatrolEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

