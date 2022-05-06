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
	StateMachine(TArray<State*>, TidesStateName);
	~StateMachine();

	//Class functionality
	TidesStateName GetActiveStateName();
	void ChangeState(TidesStateName);
	void Execute(float);

	//State action interface functions
	//template<typename stateType>
	void SendInput(StateAction);
	void SendInput(StateAction, float);
	void SendInput(StateAction Action, AActor& OtherActor);


	//Utility
	FString GetStateNameString(TidesStateName);

private:
	TMap<TidesStateName, State*> states;
	State* activeState;

};
