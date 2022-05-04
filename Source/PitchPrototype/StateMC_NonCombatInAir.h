// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_MainCharacter.h"

///	<summary>
/// This state handles in-air behavior in all circumstances
///	</summary>
class PITCHPROTOTYPE_API StateMC_NonCombatInAir : public State_MainCharacter
{
public:
	StateMC_NonCombatInAir(AMainCharacter* mainCharacter);
	~StateMC_NonCombatInAir();

protected:
	//State overrides
	void Start() override;
	void Execute(float) override;

	//State_MainCharacter overrides
	void BeginOverlapFeet() override;
	void MoveForward(float) override;
	void MoveRight(float) override;
	void LookUpRate(float) override;
	void TurnRate(float) override;

	//Internal functions
	void ApplyGravity();

	//Internal variables
	float gravityAccumulation = 0;
	float JumpDirMultiplierAlpha = 0;
};
