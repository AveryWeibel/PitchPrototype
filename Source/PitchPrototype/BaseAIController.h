// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "State.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
//Declare Macros
DECLARE_LOG_CATEGORY_EXTERN(Log171GuardAI, Log, All);

UCLASS()
class PITCHPROTOTYPE_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	UPROPERTY()
	UBehaviorTreeComponent* BehaviorComp;
	
public:
	ABaseAIController();

	UFUNCTION()
	void SetMoveTarget(FVector target);

	UFUNCTION()
	void SetAttackBool(bool state);
};
