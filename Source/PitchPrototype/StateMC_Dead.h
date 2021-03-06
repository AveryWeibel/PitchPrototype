// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_MainCharacter.h"

///	<summary>
/// Default Summary
///	</summary>
class PITCHPROTOTYPE_API StateMC_Dead : public State_MainCharacter
{
public:
	StateMC_Dead(AMainCharacter* mainCharacter);
	~StateMC_Dead();

protected:
	//State overrides
	void Start() override;
	void Execute(float) override;

	//State_MainCharacter overrides
	//virtual void MoveForward(float) override;
	//virtual void MoveRight(float) override;
	//virtual void Jump() override;
	//virtual void CollideFeet() override;
	virtual void TurnRate(float) override;
	virtual void LookUpRate(float) override;

	//Internal functions

	//Internal variables
};
