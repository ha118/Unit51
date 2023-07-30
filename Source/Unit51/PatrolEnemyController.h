// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "PatrolEnemyController.generated.h"

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

	//AI Perception Component
	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	/*Patrol Points*/
	TArray<AActor*> PatrolPoints;

	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);

	class UAISenseConfig_Sight* Sight;

	// Event when pawn is possessed
	void OnPossess(APawn* EnemyPawn) override;

public:
	// Initializing first control point
	int32 CurrentPatrolPoint = 0;
	// Constructor
	APatrolEnemyController();
	// Functions to return blackboard and patrol points
	FORCEINLINE UBlackboardComponent* GetBlackBoardComponent() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }
	
};
