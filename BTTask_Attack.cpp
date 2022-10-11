// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include "CombatInterface.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"



UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* node_memory)
{
	AAIController* const controller = OwnerComp.GetAIOwner();
	AEnemyCharacter* const enemy = Cast<AEnemyCharacter>(controller->GetPawn());
	ICombatInterface* const combat = Cast<ICombatInterface>(enemy);
	if (combat) {
		if (AttackFinish(enemy)) {
			combat->Execute_MeeleAttack(enemy);
		}
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UBTTask_Attack::AttackFinish(AEnemyCharacter* const enemy)
{
	return enemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(enemy->GetCurrentMontage());
}
