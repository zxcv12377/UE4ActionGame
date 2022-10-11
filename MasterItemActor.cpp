// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterItemActor.h"
#include "PlayerCharacter.h"

#include "Components/SphereComponent.h"

// Sets default values
AMasterItemActor::AMasterItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	//myTexture = CreateDefaultSubobject<UTexture2D>("myTexture");
	//static ConstructorHelpers::FObjectFinder<UTexture2D> TextureAsset(TEXT("Texture2D'/Game/ActionGame/Item/Image/potion.potion'"));

	/*if (TextureAsset.Succeeded()) {
		myTexture = TextureAsset.Object;
	}*/

	myMesh = CreateDefaultSubobject<UStaticMeshComponent>("myMesh");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Object) {
		myMesh->SetStaticMesh(MeshAsset.Object);
	}
	myMesh->AttachTo(Root);

	itemCollision = CreateDefaultSubobject<USphereComponent>("itemCollision");
	itemCollision->AttachTo(myMesh);

	//myMesh->SetMobility(EComponentMobility::Movable);
	// 모빌리티 설정을 무버블로 변경
	// 콜리전 활성화
}

// Called when the game starts or when spawned
void AMasterItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AMasterItemActor::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
//	{
//		APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
//		//player->itemInventory.Add(this);
//		player->isInteract = true;
//		player->Inventoryitem.Add(ItemData);
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("itemActor Destroy"));
//		//Destroy();
//	}
//}


//void AMasterItemActor::NotifyActorEndOverlap(AActor* OtherActor)
//{
//	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
//	{
//		APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
//		player->isInteract = false;
//	}
//}
//
//void AMasterItemActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector Normalmpulse, const FHitResult& Hit)
//{
//	if (Other->IsA(APlayerCharacter::StaticClass()))
//	{
//		APlayerCharacter* player = Cast<APlayerCharacter>(Other);
//		player->itemInventory.Add(this);
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("itemActor Notifying"));
//	}
//}

