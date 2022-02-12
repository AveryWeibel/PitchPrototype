// Fill out your copyright notice in the Description page of Project Settings.


#include "TickThisAttack.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTickThisAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UE_LOG(Log171General, Log, TEXT("Perform Attack Node"))
	UTidesBTTaskNode::ExecuteTask(OwnerComp, NodeMemory);
	
	AWeapon* Weapon = owningChar->Weapon;

	//OwnerComp.GetBlackboardComponent()->GetValueAsBool("WeaponActive")

	return EBTNodeResult::Succeeded;
}

