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
	//Variables/Objects managed by this state
	AMainCharacter* mainCharacter;

	FVector* movementVector = new FVector(FVector::ZeroVector);
	FRotator* cameraTurnVector = new FRotator(FRotator::ZeroRotator);
	bool grounded = false;

	//Move Inputs
	float moveFwd = 0;
	float moveRht = 0;
	float moveZ = 0;

	//Camera Inputs
	float cameraInputX = 0;
	float cameraInputY = 0;

	//Functions for managed variables
	void ConsumeMoveInputs();
	void ConsumeCameraInput();

	//Implement State SendInput
	void SendInput(StateAction) override;
	void SendInput(StateAction, float) override;

	//Input delegate methods
	//Empty definitions here so that subclasses don't all have to implement them
	virtual void MoveForward(float);
	virtual void MoveRight(float);
	virtual void TurnRate(float);
	virtual void LookUpRate(float);
	virtual void Jump();
	virtual void BeginOverlapFeet();
	virtual void EndOverlapFeet();
};