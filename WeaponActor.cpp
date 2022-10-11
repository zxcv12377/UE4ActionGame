// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActor.h"
#include "PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine.h"
#include "Components/BoxComponent.h"


void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Sets default values
AWeaponActor::AWeaponActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	Handle = CreateDefaultSubobject<USceneComponent>("WeaponHandle");
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>("WeaponCollision");
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	Handle->AttachTo(Root);
	WeaponMesh->AttachTo(Handle);
	WeaponCollision->AttachTo(WeaponMesh);
	auto ParticleAsst = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	weaponFX = ParticleAsst.Object;
}
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		if (MyPawn->WeaponCollisionchk && !Enemy->EnemyHit)
		{
			UGameplayStatics::ApplyDamage(OtherActor, WeaponAttackDamage, NULL, MyPawn, UDamageType::StaticClass());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), weaponFX, OtherActor->GetActorLocation());
			MyPawn->isHit = true;
		}
	}
}

