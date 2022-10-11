// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ItemActor.h"
#include "ItemDataActor.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	FitemDetail* dataMove(int32 Row);

private:
	class UDataTable* ItemDatatable;
	
};
