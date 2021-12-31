// Fill out your copyright notice in the Description page of Project Settings.


#include "State_MainCharacter.h"
#include "MainCharacter.h"

State_MainCharacter::State_MainCharacter(AMainCharacter* mainCharacterPtr)
{
	mainCharacter = mainCharacterPtr;
	check(mainCharacter);

	//Function pointer method (Abandoned)
	//StateAxisDelegates.Add(StateAction::MoveForward, &State_MainCharacter::MoveForward);
}

//Apply inputs for this frame to movement vector and reset them to zero
void State_MainCharacter::ConsumeMoveInputs()
{
	movementVector->Set(moveX, moveY, moveZ);
	moveX = moveY = moveZ = 0;
}

void State_MainCharacter::ConsumeCameraInput()
{
	cameraTurnVector->Add(cameraInputY, cameraInputX, 0);
	cameraInputX = cameraInputY = 0;
}

void State_MainCharacter::SendInput(StateAction Action)
{
	switch (Action) {
	case StateAction::Jump:
		Jump();
		break;
	case StateAction::BeginOverlapFeet:
		BeginOverlapFeet();
		break;
	case StateAction::EndOverlapFeet:
		EndOverlapFeet();
		break;
	default:
		break;
	}
}

void State_MainCharacter::SendInput(StateAction Action, float Value)
{
	switch (Action) {
	case StateAction::MoveForward:
		MoveForward(Value);
		break;
	case StateAction::MoveRight:
		MoveRight(Value);
		break;
	case StateAction::TurnRate:
		TurnRate(Value);
		break;
	case StateAction::LookUpRate:
		LookUpRate(Value);
		break;
	default:
		break;
	}

}

void State_MainCharacter::MoveForward(float)
{
}


void State_MainCharacter::MoveRight(float)
{
}

void State_MainCharacter::TurnRate(float)
{
}

void State_MainCharacter::LookUpRate(float)
{
}

void State_MainCharacter::Jump()
{
}

void State_MainCharacter::BeginOverlapFeet()
{
}

void State_MainCharacter::EndOverlapFeet()
{
}

State_MainCharacter::~State_MainCharacter()
{
}

