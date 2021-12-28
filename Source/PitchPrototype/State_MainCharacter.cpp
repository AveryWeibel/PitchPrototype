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

void State_MainCharacter::SendInput(StateAction Action, float Value)
{
	switch (Action) {
	case StateAction::MoveForward:
		MoveForward(Value);
		break;
	case StateAction::MoveRight:
		MoveRight(Value);
		break;
	default:
		break;
	}

}

State_MainCharacter::~State_MainCharacter()
{
}

