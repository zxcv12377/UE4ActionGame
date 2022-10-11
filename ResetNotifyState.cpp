// Fill out your copyright notice in the Description page of Project Settings.

#include "ResetNotifyState.h"
#include "PlayerCharacter.h"



void UResetNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (player != nullptr) {
		player->comboCnt = 1;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("RESET"));
	}
}
