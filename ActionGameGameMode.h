// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ActionGameGameMode.generated.h"

UCLASS(minimalapi)
class AActionGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AActionGameGameMode();

protected:
	virtual void BeginPlay() override;
};



