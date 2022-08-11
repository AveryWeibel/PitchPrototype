// Fill out your copyright notice in the Description page of Project Settings.


#include "TownGuardAnimInstance.h"

#include "BaseAICharacter.h"

void UTownGuardAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningPawn = TryGetPawnOwner();
}

TidesStateName UTownGuardAnimInstance::CheckState()
{
	return currentAnimState;
}

void UTownGuardAnimInstance::SetState(TidesStateName state)
{
	currentAnimState = state;
}

void UTownGuardAnimInstance::RecieveAnimEndNotif()
{
	Cast<ABaseAICharacter>(OwningPawn)->RecieveAnimEnd();
}

void UTownGuardAnimInstance::RecieveHitBoxActiveNotif()
{
	Cast<ABaseAICharacter>(OwningPawn)->RecieveHitboxActive();
}

void UTownGuardAnimInstance::RecieveHitBoxInactiveNotif()
{
	Cast<ABaseAICharacter>(OwningPawn)->RecieveHitboxInactive();
}

void UTownGuardAnimInstance::SetParryIKTarget(FVector value)
{
	parryIKTarget = value;
}

FVector UTownGuardAnimInstance::GetParryIKTarget()
{
	return parryIKTarget;
}

bool UTownGuardAnimInstance::GetParryable()
{
	return parryable;
}

void UTownGuardAnimInstance::SetParryable(bool value)
{
	parryable = value;
}

float UTownGuardAnimInstance::GetParryAlpha()
{
	return parryAlpha;
}

void UTownGuardAnimInstance::SetParryAlpha(float value)
{
	parryAlpha = value;
}
