// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "MainCharacter.h"

/**
 * 
 */
class PITCHPROTOTYPE_API State_MainCharacter : public State
{
public:
	State_MainCharacter(AMainCharacter*);
	~State_MainCharacter();

protected:
	AMainCharacter* mainCharacter;
};
