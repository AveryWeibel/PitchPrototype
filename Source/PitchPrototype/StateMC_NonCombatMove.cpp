// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMC_NonCombatMove.h"
#include "MainCharacter.h"

DEFINE_LOG_CATEGORY(Log171NonCombatMove);

// Call parent Ctor
StateMC_NonCombatMove::StateMC_NonCombatMove(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	stateName = StateName::NonCombatMove;
}

StateMC_NonCombatMove::~StateMC_NonCombatMove()
{
}

void StateMC_NonCombatMove::Start()
{
	//Testing code, temp temp temp
	if (stateName == StateName::NonCombatMove) {
		UE_LOG(LogTemp, Log, TEXT("Enter State"));
	}
}

void StateMC_NonCombatMove::Execute(float deltatime)
{
	movementVector->Set(moveX, moveY, moveZ);


	if (mainCharacter->feetCollider->GetPhysicsLinearVelocity().Size() <= mainCharacter->maximumHorizontalVelocity) {

		mainCharacter->feetCollider->AddForce(*movementVector);
	}

	mainCharacter->feetCollider->SetWorldRotation(FRotator(0, 0, 0));
}

void StateMC_NonCombatMove::MoveForward(float Value)
{
	if(Value != 0)
		UE_LOG(Log171NonCombatMove, Log, TEXT("CharacterVelocity[X: %f, Y: %f, Z: %f]"), mainCharacter->feetCollider->GetPhysicsLinearVelocity().X, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Y, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Z);
	
	moveX = Value * mainCharacter->accelerationForce;
}

void StateMC_NonCombatMove::MoveRight(float Value)
{
	if (Value != 0)
		UE_LOG(Log171NonCombatMove, Log, TEXT("CharacterVelocity[X: %f, Y: %f, Z: %f]"), mainCharacter->feetCollider->GetPhysicsLinearVelocity().X, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Y, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Z);

	moveY = Value * mainCharacter->accelerationForce;
}

void StateMC_NonCombatMove::Jump()
{
}
