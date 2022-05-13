// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"

#include "MainCharacter.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningPawn = TryGetPawnOwner();
}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);
}

void UMainCharacterAnimInstance::SetControlDirection(FVector value)
{
	controlDirection = value;
}

void UMainCharacterAnimInstance::SetLookAtTarget(FVector Target)
{
	lookatTarget = Target;
}

TidesStateName UMainCharacterAnimInstance::CheckState()
{
	return currentAnimState;
}

void UMainCharacterAnimInstance::NotifyAnimationEnd()
{
	auto MainChar = Cast<AMainCharacter>(OwningPawn);

	if(MainChar)
	{
		MainChar->RecieveAnimEndNotif();
	}
}

void UMainCharacterAnimInstance::NotifyAnimHitboxActive()
{
	auto MainChar = Cast<AMainCharacter>(OwningPawn);

	if(MainChar)
	{
		MainChar->RecieveAnimHitboxActive();
	}
}

void UMainCharacterAnimInstance::NotifyAnimHitboxInactive()
{
	auto MainChar = Cast<AMainCharacter>(OwningPawn);

	if(MainChar)
	{
		MainChar->RecieveAnimHitboxInactive();
	}
}

FVector UMainCharacterAnimInstance::GetControlDirection()
{
	return controlDirection;
}

void UMainCharacterAnimInstance::SetParryAlpha(float value)
{
	parryAlpha = value;
}

float UMainCharacterAnimInstance::GetParryAlpha()
{
	return parryAlpha;
}

void UMainCharacterAnimInstance::SetSheatheAlpha(float value)
{
	SheatheArmAlpha = value;
}

float UMainCharacterAnimInstance::GetSheatheAlpha()
{
	return SheatheArmAlpha;
}

void UMainCharacterAnimInstance::SetParryIKTarget(FVector value)
{
	parryIKTarget = value;
}

FVector UMainCharacterAnimInstance::GetParryIKTarget()
{
	return parryIKTarget;
}
