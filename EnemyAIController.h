// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Perception/AIPerceptionTypes.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	// 캐릭터와 연결 시켜줌
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = Behavior)
		void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);

	class UBlackboardComponent* GetBlackboard() const;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
		class UBehaviorTreeComponent* btreeComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* btree;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
		class UBlackboardComponent* blackboardComp;

	UPROPERTY()
		class UAISenseConfig_Sight* sightConfig;
};
