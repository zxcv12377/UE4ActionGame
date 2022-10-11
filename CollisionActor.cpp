// Fill out your copyright notice in the Description page of Project Settings.
#include "CollisionActor.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"



// Sets default values
ACollisionActor::ACollisionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereCollision = CreateDefaultSubobject<USphereComponent>("sphere");
	sphereCollision->InitSphereRadius(100.f);
	sphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ACollisionActor::MyOverlapBegin);
	// AddDynamic : 다이나믹 델리게이트
	// 컴포넌트에 있는 함수와 연결시켜줌
	// 델리게이트 사용시 연결될 함수는 UFUNCTION을 적어주어야함
	// 매개변수가 동일해야함

	myMesh = CreateDefaultSubobject<UStaticMeshComponent>("myMesh");

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (MeshAsset.Object) {
		myMesh->SetStaticMesh(MeshAsset.Object);
	}
	RootComponent = myMesh;

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	particle = ParticleAsset.Object;
	sphereCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACollisionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollisionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollisionActor::MyOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		// IsA : 클래스가 지정된 유형이면 true를 반환
		// StaticClass() : 클래스의 타입을 반환
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, GetActorLocation());
		// SpawnEmitterAtLocation : 파티클을 생성하고 자동으로 파괴시켜줌
		Destroy();
	}
}

