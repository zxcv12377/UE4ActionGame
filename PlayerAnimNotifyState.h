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
	// ��Ƽ���� ���۽� ȣ��

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation) override;
	// ��Ƽ���� ����� ȣ��
};
