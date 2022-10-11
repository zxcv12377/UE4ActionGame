// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickUp.h"
#include "ItemActor.h"

// Sets default values for this component's properties
UItemPickUp::UItemPickUp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	

	// ...
}


// Called when the game starts
void UItemPickUp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UItemPickUp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UItemPickUp::AddtoInventory(AItemActor* item)
{
	return Currentitem.Add(item);
}

