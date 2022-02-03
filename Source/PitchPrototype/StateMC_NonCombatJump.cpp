// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMC_NonCombatJump.h"
#include "MainCharacter.h"
#include "CustomDefines.h"

StateMC_NonCombatJump::StateMC_NonCombatJump(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	//Add new entry to StateName in State.h
	stateName = TidesStateName::NonCombatJump;
}

StateMC_NonCombatJump::~StateMC_NonCombatJump()
{

}

void StateMC_NonCombatJump::Start()
{
	UE_LOG(LogTemp, Log, TEXT("Enter State StateMC_NonCombatJump"));
	FVector JumpVector = FVector(
		movementVector->X * mainCharacter->jumpDirectionalMultiplier, //X
		movementVector->Y * mainCharacter->jumpDirectionalMultiplier, //Y
		mainCharacter->jumpForce                                      //Z
	);

	mainCharacter->feetCollider->AddImpulse(JumpVector);
}

void StateMC_NonCombatJump::Execute(float DeltaTime)
{

	//Setup moveVector	

	ApplyGravity();

	ConsumeMoveInputs();
	//Apply moveVector

	//Change to inair state once we start falling
	if (mainCharacter->feetCollider->GetPhysicsLinearVelocity().Z < 0) {
		gravityAccumulation = 0;
		RequestStateChange(TidesStateName::NonCombatInAir);
	}

	mainCharacter->feetCollider->AddForce(*movementVector * DeltaTime);

	mainCharacter->feetCollider->SetWorldRotation(FRotator(0, 0, 0));
}


void StateMC_NonCombatJump::ApplyGravity()
{
	gravityAccumulation -= mainCharacter->risingGravityAmount;
	moveZ = gravityAccumulation;
}