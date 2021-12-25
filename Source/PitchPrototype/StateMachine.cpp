// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StateMachine.h"

StateMachine::StateMachine(TArray<State*> newStates, StateName startingState)
{
	check(newStates.Num() > 0);

	for (auto state : newStates) {
		states.Add(state->GetStateName(), state);
	}

	//Initialize state
	ChangeState(startingState);
}

StateMachine::~StateMachine()
{

}

StateName StateMachine::GetActiveStateName()
{
	return activeState->GetStateName();
}

void StateMachine::ChangeState(StateName newState)
{
	activeState = *states.Find(newState);
	check(activeState);

	activeState->Start();
}

void StateMachine::Execute(float deltatime)
{
	activeState->Execute(deltatime);
}
