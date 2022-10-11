// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemActor.h"

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum ESlotType
{
	SLOT_None		UMETA(DisplayName = "None"),
	SLOT_Item		UMETA(DisplayName = "Item"),
	SLOT_Skill		UMETA(DisplayName = "Skill"),
	SLOT_Quick		UMETA(DisplayName = "Quick"),
	SLOT_Q_Item		UMETA(DisplayName = "Q_Itme"),
	SLOT_Q_Skill	UMETA(DisplayName = "Q_Skill")
};

USTRUCT(Atomic, BlueprintType)
struct FPlayerInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FPlayerInfo()
	{
		ID = TEXT("1010");
		name = FText::FromString("Warrior");
		level = 1;
		exp = 0;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* thumnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 exp;
};

UCLASS()
class ACTIONGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* cam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* BasicLocationZ0; // 바닥 부분
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* BasicLocationMiddle; // 몸 부분
	UFUNCTION()
		void MoveForward(float value);
	UFUNCTION()
		void MoveRight(float value);
	UFUNCTION()
		void Attack();
	UFUNCTION()
		void TurnAtRate(float rate);
	UFUNCTION()
		void LookAtRate(float rate);

	void Jump() override;
	void StopJumping() override;

	UFUNCTION()
		void Rolling();
	UFUNCTION()
		void StopRolling();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* comboAttackMtg;
	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* lastAttackMtg;
	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* jumpMtg;
	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* rollingMtg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAttack; // 공격중인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isJump;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isRolling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isSkill;
	bool isEndCombo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool WeaponCollisionchk;
	int8 comboCnt = 1; // 콤보 수
	float speed;
	FVector vector;
	int32 preset;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		bool isMouseCursor;
	bool isInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class AWeaponActor*> Inventory;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class AWeaponActor* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
		TArray<class AWeaponActor*> DefaultWeapon;
	//TArray<TSubclassOf<class AWeaponActor>> DefaultWeapon;

//virtual void PostInitializeComponents() override;
//컴포넌트 초기화 완료 후 호출

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		float currentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		float maxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		float currentMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		float maxMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WeaponMPAmount;
	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* HitAnimMontage; // 히트 모션

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;
	// ApplyDamage함수로 데미지를 전달 받은 경우 호출

	void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	UPROPERTY()
		class UAIPerceptionStimuliSourceComponent* stimulus;
	// AI에게 자극을 주는 컴포넌트

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FPlayerInfo playerInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* righthand;

	UPROPERTY()
		class APlayerController* playerController;
	UPROPERTY()
		class AItemActor* currentItem;
	UPROPERTY()
		class UItemPickUp* itemComponent;
	UPROPERTY()
		TArray<class AItemActor*> itemInventory;

	int8 useWeapon = 0001; //초기상태 

	///----------------------------------아이템
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TArray<struct FitemData> Inventoryitem;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* WeaponGetSkillParticle;

	UPROPERTY()
		float BaseDamage;
	UPROPERTY()
		float DamageRadius;
	UPROPERTY()
		int32 DamageType;
	UPROPERTY()
		FVector EmitterLocation;
	UPROPERTY()
		int32 AttackType;
	UPROPERTY()
		USceneComponent* DamageLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> ignore;
	//virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

	//bool isHardLanding;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* Landing;
	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* Falling;
};
