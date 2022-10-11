// Fill out your copyright notice in the Description page of Project Settings.
#include "BTTask_FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "blackboard_keys.h"
#include "NavigationSystem.h"



UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = TEXT("RandomLocation");
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	// 비헤이비어를 소유하고 있는 AI를 가져옴
	auto const enemy = controller->GetPawn();

	FVector const enemyPos = enemy->GetActorLocation();
	FNavLocation navPos;
	UNavigationSystemV1* const navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	// 현재 월드에 있는 네비게이션 시스템을 가져옴

	if (navSys->GetRandomPointInNavigableRadius(enemyPos, searchRadius, navPos, nullptr)) { 
		// 네비게이션 시스템 기반 랜덤 위치를 navPos변수에 넣어줌
		controller->GetBlackboard()->SetValueAsVector(Blackboard_Keys::targerPos, navPos.Location);
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);// 성공 전달

	return EBTNodeResult::Succeeded;
}
