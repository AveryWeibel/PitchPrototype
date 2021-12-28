// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"

class AMainCharacter;

/**
 * In-Between class that delcares and assigns variables and objects that it's subclasses will manipulate
 */

class PITCHPROTOTYPE_API State_MainCharacter : public State
{
	friend class StateMachine;

public:
	State_MainCharacter(AMainCharacter*);
	~State_MainCharacter();

	//Dictionary<MainCharacterActions, StateAxisDelegate> StateAxisDelegates;
	//Dictionary<MainCharacterActions, StateActionDelegate> StateActionDelegates;

protected:
	//Variables/Objects manipulated by this state
	AMainCharacter* mainCharacter;

	FVector* movementVector = new FVector(FVector::ZeroVector);
	bool grounded = false;

	float moveX = 0;
	float moveY = 0;
	float moveZ = 0;

	//Implement State SendInput
	void SendInput(StateAction, float) override;

	//Input delegate methods
	virtual void MoveForward(float) = 0;
	virtual void MoveRight(float) = 0;
	virtual void Jump() = 0;
};