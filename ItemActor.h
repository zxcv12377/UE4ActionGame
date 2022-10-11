// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	None		UMETA(DisplayName = "None"),
	Weapon		UMETA(DisplayName = "Weapon"),
	Head		UMETA(DisplayName = "Head"),
	Armor		UMETA(DisplayName = "Armor"),
	Shoe		UMETA(DisplayName = "Shoe"),
	Shield		UMETA(DisplayName = "Shield"),
	Necklace	UMETA(DisplayName = "Necklace"),
	FRing		UMETA(DisplayName = "FRing"),
	SRing		UMETA(DisplayName = "SRing"),
	Belt		UMETA(DisplayName = "Belt"),
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	NONE		UMETA(DisplayName = "NONE"),
	Equipment	UMETA(DisplayName = "Equipment"),
	Useable		UMETA(DisplayName = "Useable"),
	Etc			UMETA(DisplayName = "Ect"),
};
USTRUCT(Atomic, BlueprintType)
struct FitemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FitemData()
	{};
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName name; // 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* texture; // 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemType Type; // 아이템 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEquipmentType EquipType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AActor> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;// 아이템 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Count; // 갯수

};






UCLASS()
class ACTIONGAME_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
