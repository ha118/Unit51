// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPatrolPoint.h"
#include "AIPatrolPoint.h"
#include "PatrolEnemy.h"
#include "PatrolEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include <random>

EBTNodeResult::Type USelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

		/*Get Blackboard*/
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AAIPatrolPoint* PatrolPoint = Cast<AAIPatrolPoint>(Blackboard->GetValueAsObject("LocationToGo"));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), PatrolPoints);
	TArray<AActor*> AvailablePatrolPoints = PatrolPoints;
	int range = PatrolPoints.Num();
	int num = rand() % range;
	AAIPatrolPoint* CurrentPatrolPoint = Cast<AAIPatrolPoint>(PatrolPoints[num]);



	Blackboard->SetValueAsVector("LocationToGo", CurrentPatrolPoint->GetTargetLocation());

	return EBTNodeResult::Succeeded;
}
	//}
	//return EBTNodeResult::Failed;
