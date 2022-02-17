// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TidesBTTaskNode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "AI/Navigation/NavigationTypes.h"
#include "FindDialogueCombatLocation.generated.h"

/**
 * 
 */
UCLASS()
class PITCHPROTOTYPE_API UFindDialogueCombatLocation : public UTidesBTTaskNode
{
	GENERATED_BODY()

	UFindDialogueCombatLocation();

public: 

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector targetDest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float distance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float radius;
};
