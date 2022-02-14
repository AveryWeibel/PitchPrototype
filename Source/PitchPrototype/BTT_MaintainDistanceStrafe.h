// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TidesBTTaskNode.h"
#include "BTT_MaintainDistanceStrafe.generated.h"

/**
 * 
 */

UCLASS()
class PITCHPROTOTYPE_API UBTT_MaintainDistanceStrafe : public UTidesBTTaskNode
{
	GENERATED_BODY()

	UBTT_MaintainDistanceStrafe();

	virtual uint16 GetInstanceMemorySize() const override;

public:

	UPROPERTY(EditAnywhere)
		float timeBetweenAttacks;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
