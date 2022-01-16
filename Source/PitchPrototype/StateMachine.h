// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"

DECLARE_LOG_CATEGORY_EXTERN(Log171StateMachine, Error, All);

DECLARE_DELEGATE_OneParam(StateAxisDelegate, float);
/**
 * 
 */
class PITCHPROTOTYPE_API StateMachine
{
public:
	//Ctor/Dtor
	StateMachine(TArray<State*>, StateName);
	~StateMachine();

	//Class functionality
	StateName GetActiveStateName();
	void ChangeState(StateName);
	void Execute(float);

	//State action interface functions
	//template<typename stateType>
	void SendInput(StateAction);
	void SendInput(StateAction, float);


	//Utility
	FString GetStateNameString(StateName);

private:
	TMap<StateName, State*> states;
	State* activeState;

};