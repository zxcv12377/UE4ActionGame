// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "Engine.h"
#include "blackboard_keys.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AISenseConfig.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Runtime/Engine/Classes/kismet/GameplayStatics.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

#include "PlayerCharacter.h"


AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true; // ƽ�Լ� Ȱ��ȭ

	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("sightConfig");
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("Perception"));

	sightConfig->SightRadius = 500.f; // �� �� �ִ� �Ÿ�
	sightConfig->LoseSightRadius = 550.f; // �̹� �� ��ǥ���� �� �� �ִ� �Ÿ�
	sightConfig->PeripheralVisionAngleDegrees = 90.f; // �� �� �ִ� ����
	sightConfig->SetMaxAge(5.f); // �� �� �ִ� �ð�
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	// �� ����
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	// �Ʊ� ����
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	// �߸� ����
	sightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
	// ���������� �� ��ġ���� ���� ���� �ִ� ����� �ô� ���͸� �� �� �ִ� ����

	GetPerceptionComponent()->SetDominantSense(*sightConfig->GetSenseImplementation());
	// �ν� ���� ������Ʈ
	GetPerceptionComponent()->ConfigureSense(*sightConfig);
	// ���� ����
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetDetected);
	// �ν������� ����Ǿ��ٸ� OnTargerDetected�Լ� ȣ��

	btreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("btreeComp");
	blackboardComp = CreateDefaultSubobject<UBlackboardComponent>("blackboardComp");
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(btree);
	btreeComp->StartTree(*btree);
	// �����̺��Ʈ�� ����
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// �����־�� ��Ʈ�ѷ��� ĳ���Ͱ� ����
	if (blackboardComp) {
		blackboardComp->InitializeBlackboard(*btree->BlackboardAsset);
		// �����̺��Ʈ���� �ִ� ������ �ʱ�ȭ
	}
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemyAIController::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (auto const player = Cast<APlayerCharacter>(actor)) {
		GetBlackboard()->SetValueAsBool(Blackboard_Keys::isFindPlayer, stimulus.WasSuccessfullySensed());
	}
}

UBlackboardComponent* AEnemyAIController::GetBlackboard() const
{
	return blackboardComp;
}
