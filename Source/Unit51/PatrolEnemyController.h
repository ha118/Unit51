// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PatrolEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class UNIT51_API APatrolEnemyController : public AAIController
{
	GENERATED_BODY()

	UBlackboardComponent* BlackboardComp;

	class UBehaviorTreeComponent* BehaviorComp;

	/*Blackboard keys*/
	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName TargetLocation;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName PlayerKey;

	/*Patrol Points*/
	TArray<AActor*> PatrolPoints;

	void OnPossess(APawn* EnemyPawn) override;

public:
	int32 CurrentPatrolPoint = 0;
	APatrolEnemyController();
	void setPlayerCaught(APawn* EnemyPawn);
	FORCEINLINE UBlackboardComponent* GetBlackBoardComponent() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }
	
};
