// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAIController.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MainCharacter.h"
#include "TidesBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class PITCHPROTOTYPE_API UTidesBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY()
		ABaseAICharacter* owningChar;

	UFUNCTION()
		void DoAttack();
};
