// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_MainCharacter.h"

///	<summary>
/// handles movement inputs when locked on to an AI
///	</summary>
///

DECLARE_LOG_CATEGORY_EXTERN(Log171LockedOnMove, Log, All);

class PITCHPROTOTYPE_API StateMC_LockedOnMove : public State_MainCharacter
{
public:
	StateMC_LockedOnMove(AMainCharacter* mainCharacter);
	~StateMC_LockedOnMove();

protected:
	//State overrides
	void Start() override;
	void Execute(float) override;

	//State_MainCharacter overrides
	virtual void MoveForward(float) override;
	virtual void MoveRight(float) override;
	//virtual void Jump();
	//virtual void CollideFeet();
	virtual void LockOn() override;

	//Internal functions

	//Internal variables
};
