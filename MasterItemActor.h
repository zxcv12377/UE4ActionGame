// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "GameFramework/Actor.h"
#include "MasterItemActor.generated.h"

UCLASS()
class ACTIONGAME_API AMasterItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FitemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Root;
	UPROPERTY()
		class USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* myMesh;
	UPROPERTY(VisibleDefaultsOnly, Category = "item")
		class USphereComponent* itemCollision;

	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	// 액터가 겹침상태로 충돌시 호출
	//virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	//virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other,
	//	UPrimitiveComponent* OtherComp, bool bSelfMoved,
	//	FVector HitLocation, FVector HitNormal, FVector Normalmpulse,
	//	const FHitResult& Hit) override;

};
