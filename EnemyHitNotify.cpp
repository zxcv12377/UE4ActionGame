// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyHitNotify.h"
#include "EnemyCharacter.h"


void UEnemyHitNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AEnemyCharacter* enemy = Cast<AEnemyCharacter>(MeshComp->GetOwner());
	if (enemy != nullptr) {
		enemy->EnemyHit = true;
	}
}

void UEnemyHitNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AEnemyCharacter* enemy = Cast<AEnemyCharacter>(MeshComp->GetOwner());
	if (enemy != nullptr) {
		enemy->EnemyHit = false;
	}
}
