// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDataActor.generated.h"

UENUM(BlueprintType)
enum class EEquipmentDetail : uint8
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
enum class EItemTypeDetail : uint8
{
	NONE		UMETA(DisplayName = "NONE"),
	Equipment	UMETA(DisplayName = "Equipment"),
	Useable		UMETA(DisplayName = "Useable"),
	Etc			UMETA(DisplayName = "Ect"),
};
USTRUCT(Atomic, BlueprintType)
struct FitemDetail : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name; // 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* texture; // 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemTypeDetail Type; // 아이템 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEquipmentDetail EquipType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AActor> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;// 아이템 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Count; // 갯수

};

UCLASS()
class ACTIONGAME_API AItemDataActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemDataActor();
};
