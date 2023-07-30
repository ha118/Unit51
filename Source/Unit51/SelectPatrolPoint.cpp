// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPatrolPoint.h"
#include "AIPatrolPoint.h"
#include "PatrolEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APatrolEnemyController* AICon = Cast<APatrolEnemyController>(OwnerComp.GetAIOwner());

	if (AICon) {
		UBlackboardComponent* Blackboard = AICon->GetBlackboardComponent();
		AAIPatrolPoint* CurrPatrolPoint = Cast<AAIPatrolPoint>(Blackboard->GetValueAsObject("LocationToGo"));
		TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPoints();
		AAIPatrolPoint* NextPatrolPoint = nullptr;

		if (AICon->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1) {
			NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[++AICon->CurrentPatrolPoint]);
		}
		else {
			NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[0]);
			AICon->CurrentPatrolPoint = 0;
		}
		Blackboard->SetValueAsVector("LocationToGo", NextPatrolPoint->GetTargetLocation());
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
