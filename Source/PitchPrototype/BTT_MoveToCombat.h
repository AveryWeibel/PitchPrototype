// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TidesBTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BTT_MoveToCombat.generated.h"

/**
 * 
 */
UCLASS()
class PITCHPROTOTYPE_API UBTT_MoveToCombat : public UTidesBTTaskNode
{
	GENERATED_BODY()

	UBTT_MoveToCombat();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector moveTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float radius;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	UPROPERTY()
		FVector targetLocation;
};
