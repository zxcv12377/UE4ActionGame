// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UBTService_ChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_ChangeSpeed();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* node_memory) override;
	// OnBecomeRelevant : �����帧�� Ȱ��ȭ �Ǿ����� ȣ��
	FString GetStaticServiceDescription() const override;
	// Service�� ���� ������ ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float speed = 500.f;
};
