// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMC_NonCombatInAir.h"
#include "MainCharacter.h"

StateMC_NonCombatInAir::StateMC_NonCombatInAir(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	stateName = StateName::NonCombatInAir;
}

StateMC_NonCombatInAir::~StateMC_NonCombatInAir()
{
}

void StateMC_NonCombatInAir::Start()
{
	UE_LOG(LogTemp, Log, TEXT("Enter State NonCombatInAir"));
	mainCharacter->feetCollider->AddImpulse(FVector(movementVector->X * mainCharacter->jumpDirectionalMultiplier, movementVector->Y * mainCharacter->jumpDirectionalMultiplier, mainCharacter->jumpForce));

}

void StateMC_NonCombatInAir::Execute(float DeltaTime)
{
	//UE_LOG(LogTemp, Log, TEXT("Execute State NonCombatInAir"));
	ApplyGravity();
}

void StateMC_NonCombatInAir::ApplyGravity()
{
	moveZ += mainCharacter->gravityAmount;
}

