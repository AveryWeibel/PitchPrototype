// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine.h"
//need to remove pragma for mac version
DEFINE_LOG_CATEGORY(Log171StateMachine);

StateMachine::StateMachine(TArray<State*> newStates, TidesStateName startingState)
{
	check(newStates.Num() > 0);

	for (auto state : newStates) {
		state->parentStateMachine = this;
		states.Add(state->GetStateName(), state);
	}

	//Initialize state
	ChangeState(startingState);
}

StateMachine::~StateMachine()
{

}

TidesStateName StateMachine::GetActiveStateName()
{
	return activeState->GetStateName();
}

void StateMachine::ChangeState(TidesStateName newStateName)
{
	try {
		if (states.Contains(newStateName) != false) {
			activeState = states[newStateName];
			activeState->Start();
		}
		else {
			throw FString("State change request failed! (State not found, did you assign it's name?)");
		}
	}
	catch (FString StateError) {
		UE_LOG(Log171StateMachine, Error, TEXT("[%s] - %s"), *GetStateNameString(newStateName), *StateError);
	}
}

void StateMachine::Execute(float deltatime)
{
	activeState->Execute(deltatime);
}

void StateMachine::SendInput(StateAction Action)
{
	activeState->SendInput(Action);
}

void StateMachine::SendInput(StateAction Action, float Value)
{
	activeState->SendInput(Action, Value);
}

FString StateMachine::GetStateNameString(TidesStateName stateName)
{
	//This shouldn't ever return because of type safety
	FString name = FString("No State Exists");

	switch (stateName) {
	case TidesStateName::NonCombatInAir:
		name = FString("NonCombatAir");
		break;
	case TidesStateName::NonCombatJump:
		name = FString("NonCombatJump");
		break;
	case TidesStateName::NonCombatMove:
		name = FString("NonCombatMove");
		break;
	default:
		break;
	}

	return name;
}

