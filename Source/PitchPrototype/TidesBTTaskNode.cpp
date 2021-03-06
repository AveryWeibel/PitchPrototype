// Fill out your copyright notice in the Description page of Project Settings.


#include "TidesBTTaskNode.h"

EBTNodeResult::Type UTidesBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	owningChar = Cast<ABaseAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UTidesBTTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UTidesBTTaskNode::DoAttack()
{
	if(owningChar)
	{
		owningChar->DoAttack();
	}
}

