// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_Attack();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* node_memory) override;

	bool AttackFinish(class AEnemyCharacter* const enemy);

};
