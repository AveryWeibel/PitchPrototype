// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TidesBTTaskNode.h"
#include "TickThisAttack.generated.h"

/**
 * 
 */
UCLASS()
class PITCHPROTOTYPE_API UTickThisAttack : public UTidesBTTaskNode
{
	GENERATED_BODY()

	UTickThisAttack();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual uint16 GetInstanceMemorySize() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<TidesStateName> ExitState;

	bool playerDodgedAttack;

	AMainCharacter* player;
};
