// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "PlayerAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UPlayerAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation, float TotalDuration) override;
	// 노티파이 시작시 호출

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation) override;
	// 노티파이 종료시 호출
};
