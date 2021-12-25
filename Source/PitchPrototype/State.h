// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum StateName { NonCombatMove };

/**
 * Abstract state class
 * Custom state child classes implemented as needed
 */
class PITCHPROTOTYPE_API State
{
	friend class StateMachine;

public:
	State();
	virtual  ~State();
	StateName GetStateName();

protected:
	virtual void Start() = 0;
	virtual void Execute(float) = 0;

	StateName stateName;
};