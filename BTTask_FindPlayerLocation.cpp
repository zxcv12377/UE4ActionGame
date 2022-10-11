// Fill out your copyright notice in the Description page of Project Settings.
#include "BTTask_FindPlayerLocation.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacter.h"
#include "GameFramework/Character.h"



UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation()
{
	NodeName = TEXT("PlayerLocation");
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* node_memory)
{
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	// 0번째 플레이어 캐릭터를 가져옴
	
	auto const controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemyCharacter* const enemy = Cast<AEnemyCharacter>(controller->GetPawn());

	if (player) {
		controller->GetBlackboard()->SetValueAsVector(Blackboard_Keys::targerPos, player->GetActorLocation());
	}
	

	return EBTNodeResult::Succeeded;
}
