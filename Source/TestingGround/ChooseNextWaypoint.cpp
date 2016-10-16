// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGround.h"
#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UPatrolRoute* PatrolRoute = Cast<UPatrolRoute>(OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolRoute>());
	
	if (!ensure(PatrolRoute && BlackboardComp)) { return EBTNodeResult::Failed; }
	// GET PATROL POINTS
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() < 1) {
		UE_LOG(LogTemp, Warning, TEXT("A Guard is missing patrol points"));
		return EBTNodeResult::Aborted;
	}

	// SET NEXT WAYPOINT
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	
	// CYCLE INDEX
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, ++Index % PatrolPoints.Num());

	return EBTNodeResult::Succeeded;
}
