// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"

#include "BaseAICharacter.h"
#include "MainCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY(Log171GuardAI);

//AI design references code here https://www.tomlooman.com/unreal-engine-cpp-survival-sample-game/section-three/

ABaseAIController::ABaseAIController()
{
	UE_LOG(LogTemp, Log, TEXT("Print from AI constructor"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BheaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void ABaseAIController::SetMoveTarget(FVector target)
{


	if(BehaviorComp->IsRunning())
	{
		UE_LOG(LogTemp, Log, TEXT("Behavior Tree Running"))
	}

	
	if(BlackboardComp)
	{
		UE_LOG(LogTemp, Log, TEXT("CallSetTarget()"));
		BlackboardComp->SetValueAsVector("TargetDest", target);
	}
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("BaseAIBeginPlay()"));
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ABaseAICharacter* AICharacter = Cast<ABaseAICharacter>(InPawn);
	if(AICharacter)
	{
		if(AICharacter->BehaviorTree->BlackboardAsset)
		{
			if(BlackboardComp->InitializeBlackboard(*AICharacter->BehaviorTree->BlackboardAsset))
			{
				UE_LOG(LogTemp, Log, TEXT("Successfully init blackboard"))
			}
			
			//BlackboardComp->SetValueAsEnum()
		}
		BehaviorComp->StartTree(*AICharacter->BehaviorTree);
	}
	
}

