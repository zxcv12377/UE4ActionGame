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
	// �����̺� �����ϰ� �ִ� AI�� ������
	auto const enemy = controller->GetPawn();

	FVector const enemyPos = enemy->GetActorLocation();
	FNavLocation navPos;
	UNavigationSystemV1* const navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	// ���� ���忡 �ִ� �׺���̼� �ý����� ������

	if (navSys->GetRandomPointInNavigableRadius(enemyPos, searchRadius, navPos, nullptr)) { 
		// �׺���̼� �ý��� ��� ���� ��ġ�� navPos������ �־���
		controller->GetBlackboard()->SetValueAsVector(Blackboard_Keys::targerPos, navPos.Location);
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);// ���� ����

	return EBTNodeResult::Succeeded;
}
