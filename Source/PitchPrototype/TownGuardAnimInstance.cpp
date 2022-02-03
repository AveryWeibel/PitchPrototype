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

void UTownGuardAnimInstance::RecieveAnimEndNotif()
{
	Cast<ABaseAICharacter>(OwningPawn)->RecieveAnimEnd();
}
