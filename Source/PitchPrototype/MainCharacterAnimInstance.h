// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "Animation/AnimInstance.h"
#include "MainCharacterAnimInstance.generated.h"

/**
 * Modified code from https://www.youtube.com/watch?v=vQyvaRbR_SM&t=845s
 * 
 */
UENUM(BlueprintType) // Animation type for the character
enum class EAnimationType : uint8
{
	VE_NONE 		    UMETA(DisplayName = "None"),
	VE_DISMISS		    UMETA(DisplayName = "Dismiss"),
	VE_INTERACT		    UMETA(DisplayName = "Interact"),
	VE_PUSH             UMETA(DisplayName = "Push"),
};

UCLASS()
class PITCHPROTOTYPE_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:



	APawn* OwningPawn;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	UFUNCTION(BlueprintCallable, Category = "Animation Dynamics")
	void SetTurnAmount(float Value);

	UFUNCTION(BlueprintCallable, Category = "Animation Dynamics")
		void SetControlDirection(FVector value);
	
	UFUNCTION(BlueprintCallable, Category = "Animation Dynamics")
		void SetTiltAmount(float Value);

	UFUNCTION(BlueprintCallable, Category = "Animation Dynamics")
		void SetLookAtTarget(FVector Target);

	UFUNCTION(BlueprintCallable, Category = "Animation Dynamics")
		float GetTiltAmount();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "UpdateState"))
		void RecieveStateUpdate(TidesStateName name);

	UFUNCTION(BlueprintCallable)
		TidesStateName CheckState();

	UFUNCTION(BlueprintCallable)
		void NotifyAnimationEnd();

	UFUNCTION(BlueprintCallable)
		void NotifyAnimHitboxActive();
	
	UFUNCTION(BlueprintCallable)
		void NotifyAnimHitboxInactive();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Settings")
		EAnimationType CurrentAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
		float turnAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
		float tiltAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		FVector controlDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		FVector lookatTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		TEnumAsByte<TidesStateName> currentAnimState;

public:
	FORCEINLINE void SetAnimation(EAnimationType Value) { CurrentAnimation = Value; }

	FORCEINLINE EAnimationType GetAnimation() { return CurrentAnimation; }
};
