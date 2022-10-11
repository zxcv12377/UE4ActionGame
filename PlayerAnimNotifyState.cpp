// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerAnimNotifyState.h"
#include "PlayerCharacter.h"


void UPlayerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, __FUNCTION__);

	APlayerCharacter* player = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (player != nullptr) {
		player->isAttack = true;
	}
}


void UPlayerAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, __FUNCTION__);

	APlayerCharacter* player = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (player != nullptr) {
		player->isAttack = false;
		player->isHit = false;
	}
}
