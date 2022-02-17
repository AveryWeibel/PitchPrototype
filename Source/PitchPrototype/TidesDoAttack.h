// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TidesBTTaskNode.h"
#include "TidesDoAttack.generated.h"

/**
 * 
 */
UCLASS()
class PITCHPROTOTYPE_API UTidesDoAttack : public UTidesBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
