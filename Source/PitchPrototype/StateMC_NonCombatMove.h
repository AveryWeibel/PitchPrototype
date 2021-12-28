// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_MainCharacter.h"

DECLARE_LOG_CATEGORY_EXTERN(Log171NonCombatMove, Log, All);
/**
 * 
 */
class PITCHPROTOTYPE_API StateMC_NonCombatMove : public State_MainCharacter
{
public:
	StateMC_NonCombatMove(AMainCharacter*);
	~StateMC_NonCombatMove();

	//State overrides
	void Start() override;
	void Execute(float) override;

	//State_MainCharacter overrides
	void MoveForward(float);
	void MoveRight(float);
	void Jump();

};
