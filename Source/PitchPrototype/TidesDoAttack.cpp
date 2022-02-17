// Fill out your copyright notice in the Description page of Project Settings.


#include "TidesDoAttack.h"

EBTNodeResult::Type UTidesDoAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UE_LOG(Log171General, Log, TEXT("Perform Attack Node"))
	UTidesBTTaskNode::ExecuteTask(OwnerComp, NodeMemory);

	DoAttack();

	return EBTNodeResult::Succeeded;
}
