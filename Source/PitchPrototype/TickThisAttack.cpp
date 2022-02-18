// Fill out your copyright notice in the Description page of Project Settings.


#include "TickThisAttack.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTickThisAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UE_LOG(Log171General, Log, TEXT("Perform Attack Node"))
	UTidesBTTaskNode::ExecuteTask(OwnerComp, NodeMemory);

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
	}
	
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UTickThisAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("WeaponActive", false);
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UTickThisAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

