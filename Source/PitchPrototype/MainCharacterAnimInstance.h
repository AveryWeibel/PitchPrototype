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
		void SetControlDirection(FVector value);

	UFUNCTION(BlueprintCallable, Category = "Animation Dynamics")
		void SetLookAtTarget(FVector Target);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "UpdateState"))
		void RecieveStateUpdate(TidesStateName name);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "StartIntroMontage"))
	void StartIntroMontage();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "StartAttackMontage"))
	void StartAttackMontage();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "StartParryMontage"))
	void StartParryMontage();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "GetMontageTime"))
	float GetMontageTime();
	
	UFUNCTION(BlueprintCallable)
		TidesStateName CheckState();

	UFUNCTION(BlueprintCallable)
		void NotifyAnimationEnd();

	UFUNCTION(BlueprintCallable)
		void NotifyAnimHitboxActive();
	
	UFUNCTION(BlueprintCallable)
		void NotifyAnimHitboxInactive();

	UFUNCTION(BlueprintCallable)
		void NotifyIntroAnimEnd();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Settings")
		EAnimationType CurrentAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		FVector controlDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		FVector lookatTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		TEnumAsByte<TidesStateName> currentAnimState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float parryAlpha;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		FVector parryIKTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
		float SheatheArmAlpha = 0.0f;

public:
	FVector GetControlDirection();
	
	FORCEINLINE void SetAnimation(EAnimationType Value) { CurrentAnimation = Value; }

	FORCEINLINE EAnimationType GetAnimation() { return CurrentAnimation; }
	
	UFUNCTION(BlueprintImplementableEvent)
		void PlayParry();

	UFUNCTION()
		void SetParryAlpha(float value);

	UFUNCTION()
		float GetParryAlpha();

	UFUNCTION()
		void SetSheatheAlpha(float value);

	UFUNCTION()
		float GetSheatheAlpha();

	UFUNCTION()
		void SetParryIKTarget(FVector value);

	UFUNCTION()
		FVector GetParryIKTarget();

	UFUNCTION(BlueprintImplementableEvent)
		void ParrySound();

	UFUNCTION(BlueprintImplementableEvent)
		void LandedOnGround();
};
