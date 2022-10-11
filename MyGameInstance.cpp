// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "UObject/ConstructorHelpers.h"


UMyGameInstance::UMyGameInstance()
{
	ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("DataTable'/Game/ActionGame/Itemdata.Itemdata'"));
	if (DataTable.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("DataTable Loading Successed"));
		ItemDatatable = DataTable.Object;
	}
}

FitemDetail* UMyGameInstance::dataMove(int32 Row)
{
	FString rowName = FString::FromInt(Row);
	FName name = FName(*rowName);
	UE_LOG(LogTemp, Warning, TEXT("DataMove Successed"));
	return ItemDatatable->FindRow<FitemDetail>(name, TEXT(""));
}
