// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"
#include "StateMachine.h"

State::State()
{
	
}

State::~State()
{
}

void State::RequestStateChange(StateName newState)
{
	parentStateMachine->ChangeState(newState);
}

void State::Start()
{
	
}

void State::Execute(float deltatime)
{


}

StateName State::GetStateName()
{
	return stateName;
}

