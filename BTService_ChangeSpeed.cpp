// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_ChangeSpeed.h"

#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"



UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	// BecomeRelevant 함수 사용
	NodeName = TEXT("ChangeSpeed");
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* node_memory)
{
	Super::OnBecomeRelevant(OwnerComp, node_memory);
	auto const controller = OwnerComp.GetAIOwner();
	AEnemyCharacter* const enemy = Cast<AEnemyCharacter>(controller->GetPawn());
	enemy->GetCharacterMovement()->MaxWalkSpeed = speed;
}

FString UBTService_ChangeSpeed::GetStaticServiceDescription() const
{
	return FString("ChangeSpeed");
}
