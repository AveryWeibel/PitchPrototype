// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningPawn = TryGetPawnOwner();
}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);
}

void UMainCharacterAnimInstance::SetTurnAmount(float Value)
{
	turnAmount = Value;
}

void UMainCharacterAnimInstance::SetControlDirection(FVector value)
{
	controlDirection = value;
}

void UMainCharacterAnimInstance::SetTiltAmount(float Value)
{
	tiltAmount = Value;
}

void UMainCharacterAnimInstance::SetLookAtTarget(FVector Target)
{
	lookatTarget = Target;
}

float UMainCharacterAnimInstance::GetTiltAmount()
{
	return tiltAmount;
}
