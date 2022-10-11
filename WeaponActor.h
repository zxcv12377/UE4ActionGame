// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class ACTIONGAME_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	AWeaponActor();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		class UBoxComponent* WeaponCollision;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
		USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		class USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		class APlayerCharacter* MyPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Handle;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	// 액터가 겹침상태로 충돌시 호출

	UPROPERTY(EditDefaultsOnly, Category = "BasicSetting")
		UParticleSystem* weaponFX;
	UPROPERTY()
		AEnemyCharacter* enemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicSetting")
		UParticleSystem* WeaponSkillFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicSetting")
		float UseManaAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicSetting")
		float WeaponAttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicSetting")
		class AWeaponActor* WeaponClass;
};
