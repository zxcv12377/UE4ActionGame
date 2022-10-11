// Fill out your copyright notice in the Description page of Project Settings.
#include "WeaponCollisionNotifyState.h"
#include "WeaponActor.h"
#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"


void UWeaponCollisionNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (player != nullptr) {
		//player->CurrentWeapon->WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		player->WeaponCollisionchk = true;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Begin"));
	}
}

void UWeaponCollisionNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (player != nullptr) {
		//player->CurrentWeapon->WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		player->WeaponCollisionchk = false;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("End"));
	}
}
