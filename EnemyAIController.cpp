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
	PrimaryActorTick.bCanEverTick = true; // 틱함수 활성화

	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("sightConfig");
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("Perception"));

	sightConfig->SightRadius = 500.f; // 볼 수 있는 거리
	sightConfig->LoseSightRadius = 550.f; // 이미 본 목표물을 볼 수 있는 거리
	sightConfig->PeripheralVisionAngleDegrees = 90.f; // 볼 수 있는 각도
	sightConfig->SetMaxAge(5.f); // 볼 수 있는 시간
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	// 적 인지
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	// 아군 인지
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	// 중립 인지
	sightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
	// 마지막으로 본 위치에서 범위 내에 있는 경우라면 봤던 액터를 볼 수 있는 범위

	GetPerceptionComponent()->SetDominantSense(*sightConfig->GetSenseImplementation());
	// 인식 정보 업데이트
	GetPerceptionComponent()->ConfigureSense(*sightConfig);
	// 감지 구성
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetDetected);
	// 인식정보가 변경되었다면 OnTargerDetected함수 호출

	btreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("btreeComp");
	blackboardComp = CreateDefaultSubobject<UBlackboardComponent>("blackboardComp");
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(btree);
	btreeComp->StartTree(*btree);
	// 비헤이비어트리 시작
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// 적어주어야 컨트롤러와 캐릭터가 연결
	if (blackboardComp) {
		blackboardComp->InitializeBlackboard(*btree->BlackboardAsset);
		// 비헤이비어트리에 있는 블랙보드 초기화
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
