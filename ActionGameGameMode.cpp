// Copyright Epic Games, Inc. All Rights Reserved.

#include "ActionGameGameMode.h"
#include "ActionGameCharacter.h"
#include "Engine/DataTable.h"
#include "ItemActor.h"
#include "WeaponActor.h"
#include "ItemDataActor.h"
#include "UObject/ConstructorHelpers.h"

AActionGameGameMode::AActionGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

//FitemData* AActionGameGameMode::namecast(FString itemname)
//{
//
//	return ItemDatatable->FindRow<FitemData>(FName(*itemname), TEXT(""));
//}

void AActionGameGameMode::BeginPlay()
{
	Super::BeginPlay();
	//if (ItemDatatable != nullptr) {
	//	for (int32 i = 0; i < 4; i++) {
	//		FString rowName = "NewRow" + FString::FromInt(i);
	//		FName name = FName(*rowName);
	//		FitemData* itemData = ItemDatatable->FindRow<FitemData>(name, TEXT(""));
	//		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Description : %s"), (*itemData).Description));
	//		//GetWorld()->SpawnActor<AWeaponActor>((*itemData).ItemClass);
	//		//UE_LOG(LogTemp, Warning, TEXT("Description : %s"), (*itemData).Description);
	//	}
	//}
	/*auto List = ItemDatatable->GetRowNames();
	D_name = List[FMath::RandRange(0, 1)];
	FitemData* ObjectDataTable = ItemDatatable->FindRow<FitemData>(D_name, FString(""));
	UE_LOG(LogTemp, Warning, TEXT("Table Name : %s"), *D_name.ToString());*/
}
