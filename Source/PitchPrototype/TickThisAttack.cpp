// Fill out your copyright notice in the Description page of Project Settings.


#include "TickThisAttack.h"

#include "BehaviorTree/BlackboardComponent.h"

struct FTickThisAttackMemory
{
	bool weaponActive;
};

UTickThisAttack::UTickThisAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UTickThisAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UE_LOG(Log171General, Log, TEXT("Perform Attack Node"))
	UTidesBTTaskNode::ExecuteTask(OwnerComp, NodeMemory);

	//FTickThisAttackMemory* TaskMemory = reinterpret_cast<FTickThisAttackMemory*>(NodeMemory);
	
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UTickThisAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FinishLatentTask(OwnerComp ,EBTNodeResult::Aborted);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("WeaponActive", false);
	UE_LOG(Log171General, Log, TEXT("Abort attack ticking task"));
	return EBTNodeResult::Aborted;
}

void UTickThisAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(OwnerComp.GetBlackboardComponent()->GetValueAsBool("RecieveAnimEnd"))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("RecieveAnimEnd", false);
		ABaseAIController* AIController = Cast<ABaseAIController>(owningChar->GetController());
		
		if (AIController)
		{
			AIController->UpdateState(ExitState, owningChar->Animator);
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("WeaponActive", false);
		FinishLatentTask(OwnerComp ,EBTNodeResult::Succeeded);
	}

	//FTickThisAttackMemory* TaskMemory = reinterpret_cast<FTickThisAttackMemory*>(NodeMemory);

	bool weaponActive = OwnerComp.GetBlackboardComponent()->GetValueAsBool("WeaponActive");
	
	auto hitPlayer = Cast<AMainCharacter>(owningChar->Weapon->overlappedPawn);

	// if(hitPlayer)
	// {
	// 	UE_LOG(Log171GuardAI, Log, TEXT("AI Weapon overlaps player"));
	// }
	
	if(weaponActive && hitPlayer)
	{
		hitPlayer->TakeWeaponHit();
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("WeaponActive", false);
		FinishLatentTask(OwnerComp ,EBTNodeResult::Succeeded);
	}
}

uint16 UTickThisAttack::GetInstanceMemorySize() const
{
	return sizeof(FTickThisAttackMemory);
}

