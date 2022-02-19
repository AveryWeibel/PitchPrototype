// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TidesBTTaskNode.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTT_SetFocus.generated.h"

/**
 * 
 */
UCLASS()
class PITCHPROTOTYPE_API UBTT_SetFocus : public UTidesBTTaskNode
{
	GENERATED_BODY()

		UBTT_SetFocus();

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool focus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector focusPawn;
};
