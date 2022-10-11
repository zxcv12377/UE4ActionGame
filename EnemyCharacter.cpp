// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemyCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "ItemActor.h"
#include "Components/CapsuleComponent.h"
#include "MyGameInstance.h"
#include "ctime"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	maxHP = 100.f;
	currentHP = maxHP;

	hitCollision = CreateDefaultSubobject<USphereComponent>("hitCollision");
	hitCollision->AttachTo(GetMesh(), "RightHand");
	// ½ºÄÌ·¹Å» ¸Þ½¬ÀÇ RightHand º»¿¡ ºÎÂø
	hitCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::MyBeginOverlap);
	isAttack = false;
	isHit = false;
	EnemyHit = false;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::MeeleAttack_Implementation()
{
	float playtime;
	FTimerHandle Timer;
	isAttack = true;
	playtime = PlayAnimMontage(attackMontage, 2.f);
	GetWorldTimerManager().SetTimer(Timer, this, &AEnemyCharacter::AttackStop, playtime, false);
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = 0;
	auto player = Cast<APlayerCharacter>(DamageCauser);
	damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Damage : %f"), damage));
	currentHP -= damage;
	if (currentHP <= 0)
	{
		player->ignore.Add(this);
		float ptime;
		FTimerHandle playtime;
		player->playerInfo.exp += 50;
		ptime = PlayAnimMontage(DieMontage, 1.0f);
		ptime -= 0.3f;
		int percentage = (rand() % 10 + 1);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("%d"), percentage));
		if (percentage > 3) {
			srand((unsigned int)time(NULL));
			int row = (rand() % 2) + 1;
			DropItemData(row);
		}
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorld()->GetTimerManager().SetTimer(playtime, FTimerDelegate::CreateLambda([&]()
			{
				Destroy();
				GetWorld()->GetTimerManager().ClearTimer(playtime);
			}), ptime, false);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("%d"), player->playerInfo.exp));
		
	}
	else {
		PlayAnimMontage(HitMontage, 2.f);
	}
	return damage;
}

void AEnemyCharacter::MyBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()) && OtherActor != this && isAttack) {
		UGameplayStatics::ApplyDamage(OtherActor, 10.f, NULL, this, UDamageType::StaticClass());
		isAttack = false;
	}
	
}

void AEnemyCharacter::DropItemData(int32 idx)
{
	UMyGameInstance* Gameinstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	FVector loc = GetActorLocation();
	if (Gameinstance != nullptr) {
		auto currentitemData = Gameinstance->dataMove(idx);
		if (currentitemData) {
			auto dropItem = GetWorld()->SpawnActor(currentitemData->ItemClass, &loc);
		}
	}
}

void AEnemyCharacter::AttackStop()
{
	isAttack = false;
}

