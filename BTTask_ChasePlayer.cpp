// Fill out your copyright notice in the Description page of Project Settings.
#include "BTTask_ChasePlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "blackboard_keys.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"



UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
	NodeName = TEXT("ChasePlayer");
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* node_memory)
{
	AEnemyAIController* const controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemyCharacter* const enemy = Cast<AEnemyCharacter>(controller->GetPawn());
	FVector const playerPos = controller->GetBlackboard()->GetValueAsVector(Blackboard_Keys::targerPos);
	// 블랙보드에 저장된 값을 가져옴
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, playerPos);
	// 목적지까지 폰을 이동시켜줌
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	// FinishLatentTask : 태스크 종료

	return EBTNodeResult::Succeeded;
}
