// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CombatInterface.h"
#include "ItemActor.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class ACTIONGAME_API AEnemyCharacter : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MeeleAttack_Implementation();
	// 인터페이스 함수를 호출하려면 Implementation을 적어주어야 함

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* attackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* HitMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* DieMontage;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float currentHP;
	float maxHP;
	bool isAttack;
	bool isHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* hitCollision;		

	UFUNCTION()
		void MyBeginOverlap(UPrimitiveComponent* HitComp, 
			AActor* OtherActor, UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
		bool EnemyHit;

	UFUNCTION()
		void DropItemData(int32 idx);

	UFUNCTION()
		void AttackStop();

};
