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
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta=(DisplayName = "RecieveStateUpdate"))
	void RecieveStateUpdate(TidesStateName name);

	UFUNCTION(BlueprintCallable)
		TidesStateName CheckState();

	UFUNCTION(BlueprintCallable)
		void RecieveAnimEndNotif();

	UFUNCTION(BlueprintCallable)
		void RecieveHitBoxActiveNotif();

	UFUNCTION(BlueprintCallable)
		void RecieveHitBoxInactiveNotif();

	UPROPERTY(BlueprintReadWrite)
		FVector parryIKTarget;

	UFUNCTION()
		void SetParryIKTarget(FVector value);

	UFUNCTION()
		FVector GetParryIKTarget();

	UFUNCTION()
		bool GetParryable();

	UFUNCTION()
		void SetParryable(bool value);

	UPROPERTY(BlueprintReadWrite)
		float parryAlpha;

	UFUNCTION(BlueprintCallable)
		float GetParryAlpha();

	UFUNCTION(BlueprintCallable)
		void SetParryAlpha(float value);

	UFUNCTION(BlueprintImplementableEvent)
		void ParrySound();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		bool parryable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		TEnumAsByte<TidesStateName> currentAnimState;
	
};
