// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "MainCharacter.h"

/**
 * In-Between class that delcares and assigns variables and objects that it's subclasses will manipulate
 */
class PITCHPROTOTYPE_API State_MainCharacter : public State
{
	friend class StateMachine;

public:
	State_MainCharacter(AMainCharacter*);
	~State_MainCharacter();

protected:
	AMainCharacter* mainCharacter;

	//Input delegate methods
	virtual void MoveForward(float) = 0;
};
