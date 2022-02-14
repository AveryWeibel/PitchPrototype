// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_MaintainDistanceStrafe.h"

#include "GameFramework/CharacterMovementComponent.h"

struct BTT_MaintainDistanceStrafeMemory
{
	float taskStartTime = 5;
};

UBTT_MaintainDistanceStrafe::UBTT_MaintainDistanceStrafe()
{
	bNotifyTick = true;
	bCreateNodeInstance = false;
}

uint16 UBTT_MaintainDistanceStrafe::GetInstanceMemorySize() const
{
	return sizeof(BTT_MaintainDistanceStrafeMemory);
}

EBTNodeResult::Type UBTT_MaintainDistanceStrafe::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Make sure to call super to initialize varibales
	Super::ExecuteTask(OwnerComp, NodeMemory);

	
	BTT_MaintainDistanceStrafeMemory* TaskMemory = reinterpret_cast<BTT_MaintainDistanceStrafeMemory*>(NodeMemory);
	
	TaskMemory->taskStartTime = owningChar->GetWorld()->GetTimeSeconds();
	UE_LOG(Log171GuardAI, Log, TEXT("Strafe Execute at %f"), TaskMemory->taskStartTime);//owningChar == NULL ? TEXT("NULL") : TEXT("NOT NULL"));
	return EBTNodeResult::InProgress;
}

void UBTT_MaintainDistanceStrafe::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	BTT_MaintainDistanceStrafeMemory* TaskMemory = reinterpret_cast<BTT_MaintainDistanceStrafeMemory*>(NodeMemory);
	
	const float executingTime = owningChar->GetWorld()->GetTimeSeconds() - TaskMemory->taskStartTime;

	owningChar->GetCharacterMovement()->MoveSmooth(owningChar->GetActorRightVector() * 100, DeltaSeconds);
	
	UE_LOG(Log171GuardAI, Log, TEXT("Strafe Tick for %f"), executingTime);

	if(executingTime >= timeBetweenAttacks)
	{
		ABaseAIController* AIController = Cast<ABaseAIController>(owningChar->GetController());
	
		UE_LOG(LogTemp, Log, TEXT("See Player"))
		if(AIController)
		{
			UE_LOG(LogTemp, Log, TEXT("Valid Controller"))
			AIController->UpdateState(TidesStateName::AI_AttemptAttack, owningChar->Animator);
			//AIController->UpdateState(TidesStateName::AI_NonCombatIdle, Animator);
		}
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
