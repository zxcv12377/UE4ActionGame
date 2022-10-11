// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerCharacter.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

#include "Engine.h"
#include "WeaponActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "ItemPickUp.h"
#include "ItemActor.h"
#include "MyGameInstance.h"
#include "ActionGameGameMode.h"
#include "UObject/ConstructorHelpers.h"



// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>("springArm");
	springArm->SetupAttachment(RootComponent);
	// SetupAttachment : 컴포넌트 부착
	springArm->TargetArmLength = 500.f;
	springArm->bUsePawnControlRotation = false; // true
	// 컨트롤러의 회전에 따라 같이 회전하도록

	cam = CreateDefaultSubobject<UCameraComponent>("Camera");
	cam->SetupAttachment(springArm);
	cam->bUsePawnControlRotation = false;
	// 컨트롤러의 회전에 따라 회전 불가

	BasicLocationZ0 = CreateDefaultSubobject<USceneComponent>("BasicLocationZ0");
	BasicLocationZ0->SetupAttachment(RootComponent);



	cam->SetRelativeTransform(FTransform(FRotator(-25.f, 0.f, 0.f), FVector(100.f, 0.f, 250.f), FVector(0, 0, 0)));

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 이동방향에 따라 캐릭터를 회전시켜줌
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// 컨트롤러의 Yaw방향에 따라 회전하지 않도록

	itemComponent = CreateDefaultSubobject<UItemPickUp>("itemComponent");

	maxHP = 100;
	maxMP = 100;
	currentHP = maxHP;
	currentMP = maxMP;

	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("stimulus");
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	// 지정된 (Sight)감지 클래스의 소스로 등록
	stimulus->RegisterWithPerceptionSystem();
	// 인식 시스템에 등록
	isHit = false;
	isJump = false;
	isRolling = false;
	isSkill = false;
	isMouseCursor = false;
	isEndCombo = false;
	WeaponCollisionchk = false;
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	preset = 0;
	BasicLocationMiddle = CreateDefaultSubobject<USceneComponent>("BasicLocationMiddle");
	BasicLocationMiddle->SetupAttachment(RootComponent);
	righthand = CreateDefaultSubobject<USceneComponent>(TEXT("righthand"));
	righthand->AttachTo(GetMesh(), "RightHand");
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	speed = FVector::DotProduct(GetVelocity(), GetActorRotation().Vector());
	if (isRolling && GetVelocity().Size() <= 0)
	{
		SetActorLocation(GetActorLocation() + (GetActorForwardVector() * 5.f));
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookAtRate);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJumping);
	PlayerInputComponent->BindAction("Rolling", IE_Pressed, this, &APlayerCharacter::Rolling);
}

void APlayerCharacter::MoveForward(float value)
{
	if ((Controller != nullptr) && (value != 0.0f) && !isAttack && !isJump && !isSkill && !isMouseCursor) {
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		// FRotationMatrix : 회전값을 행렬로 변환
		// GetUnitAxis : 회전행렬의 길이축
		AddMovementInput(Direction, value);
		vector = Direction;
	}
}

void APlayerCharacter::MoveRight(float value)
{
	if ((Controller != nullptr) && (value != 0.0f) && !isAttack && !isJump && !isSkill && !isMouseCursor) {
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
		vector = Direction;
	}
}

void APlayerCharacter::Attack()
{
	if (!isAttack && !isJump && !isRolling && !isSkill && !isMouseCursor && DefaultWeapon.Num() != 0) {
		float playTime;
		if (comboCnt < 4) {
			FString playSection = "Attack" + FString::FromInt(comboCnt);
			playTime = PlayAnimMontage(comboAttackMtg, 1.7f, FName(*playSection));
			comboCnt++;
		}
		else {
			playTime = PlayAnimMontage(lastAttackMtg, 1.7f);
			comboCnt = 1;
		}
		isAttack = true;
	}
}

void APlayerCharacter::TurnAtRate(float rate)
{
	if (!isMouseCursor) {
		AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void APlayerCharacter::LookAtRate(float rate)
{
	if (!isMouseCursor) {
		AddControllerPitchInput(rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void APlayerCharacter::Jump() // 점프 시작
{
	comboCnt = 1;
	if (!isJump && !isAttack && !isRolling && !isSkill && !isMouseCursor) {
		isJump = true;
		bPressedJump = true;
	}
}

void APlayerCharacter::StopJumping() // 점프 멈춤
{
	isJump = false;
	bPressedJump = false;
}

void APlayerCharacter::Rolling()
{
	float playtime;
	FTimerHandle Timer;
	comboCnt = 1;
	if (!isRolling && !isJump && !isSkill && !isMouseCursor)
	{
		isRolling = true;
		playtime = PlayAnimMontage(rollingMtg, 1.7f);
		GetWorldTimerManager().SetTimer(Timer, this, &APlayerCharacter::StopRolling, playtime - 0.5f, false);
	}
}

void APlayerCharacter::StopRolling()
{
	isRolling = false;
	isAttack = false;
}

//void APlayerCharacter::PostInitializeComponents()
//{
//	Super::PostInitializeComponents();
//	SpawnDefaultInventory();
//}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	// 부모함수를 호출 받은 데미지를 damage변수에 넣어줌
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("PlayerDamaged : %f"), damage));
	currentHP -= damage; // 현재 체력에서 받은 데미지를 차감
	if (currentHP <= 0) {
		Die(damage, DamageEvent, EventInstigator, DamageCauser); // 현재 액터 제거
	}
	if (!isAttack && !isRolling && !isSkill) { // 공격중이 아니라면
		PlayAnimMontage(HitAnimMontage, 1.7f); // 히트 몽타주 재생
	}

	return damage;
}

void APlayerCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 콜리전 없음
	GetCharacterMovement()->StopMovementImmediately();
	// 이동 중지
	GetCharacterMovement()->DisableMovement();
	// 이동 비활성화
	Controller->UnPossess();
	// 컨트롤러와 연결 해제
	// 죽는 모션 몽타주 넣어주기
	Destroy();
}

