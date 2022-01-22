// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum StateName { NonCombatMove, NonCombatInAir, NonCombatJump, LockedOnMove };
enum StateAction 
{ 
	MoveForward,
	MoveRight,
	Jump, 
	BeginOverlapFeet, 
	EndOverlapFeet, 
	TurnRate,
	LookUpRate,
	LockOn
};

class StateMachine;

/**
 * Abstract state class
 * Custom state child classes implemented as needed
 */
class PITCHPROTOTYPE_API State
{
	friend class StateMachine;

	typedef void (* NewFunction)(float);

public:
	State();
	virtual  ~State();
	StateName GetStateName();

protected:

	//Attempts to change the state to given StateName
	void RequestStateChange(StateName);

	//Fundamental state Overrides
	virtual void Start() = 0;
	virtual void Execute(float) = 0;

	//Input function dispatchers
	virtual void SendInput(StateAction Action) = 0;
	virtual void SendInput(StateAction Action, float Value) = 0;

	TMap<StateAction, NewFunction> StateAxisDelegates;

	StateName stateName;

private:
	StateMachine* parentStateMachine;
};