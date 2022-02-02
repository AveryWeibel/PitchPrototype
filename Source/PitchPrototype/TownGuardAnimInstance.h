// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "Animation/AnimInstance.h"
#include "TownGuardAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PITCHPROTOTYPE_API UTownGuardAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	APawn* OwningPawn;
	
	virtual void NativeInitializeAnimation() override;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta=(DisplayName = "UpdateState"))
	void RecieveStateUpdate(TidesStateName name);

	UFUNCTION(BlueprintCallable)
		TidesStateName CheckState();

	UFUNCTION(BlueprintCallable)
		void RecieveAnimEndNotif();
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	TEnumAsByte<TidesStateName> currentAnimState;
	
};
