// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_MainCharacter.h"

/**
 * 
 */
class PITCHPROTOTYPE_API StateMC_NonCombatMove : public State_MainCharacter
{
public:
	StateMC_NonCombatMove(AMainCharacter*);
	~StateMC_NonCombatMove();

	void Start() override;
	void Execute(float) override;

	FString testStr = "Some test text";
};
