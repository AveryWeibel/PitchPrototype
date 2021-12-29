// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_MainCharacter.h"

///	<summary>
/// Default Summary
///	</summary>
class PITCHPROTOTYPE_API <ClassName> : public State_MainCharacter
{
public:
	<ClassName>(AMainCharacter* mainCharacter);
	~<ClassName>();

protected:
	//State overrides
	void Start() override;
	void Execute(float) override;

	//State_MainCharacter overrides
	//virtual void MoveForward(float);
	//virtual void MoveRight(float);
	//virtual void Jump();
	//virtual void CollideFeet();

	//Internal functions

	//Internal variables
};
