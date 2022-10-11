// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UBTTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_FindRandomLocation();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	// 노드 실행시 호출되는 함수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search")
		float searchRadius = 1500.f;
};
