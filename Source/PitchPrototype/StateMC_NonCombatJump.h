// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_MainCharacter.h"

///	<summary>
/// This state handles character speed, movement and duration while rising in a jump
///	</summary>

DECLARE_LOG_CATEGORY_EXTERN(Log171NonCombatJump, Log, All);
class PITCHPROTOTYPE_API StateMC_NonCombatJump : public State_MainCharacter
{
public:
	StateMC_NonCombatJump(AMainCharacter* mainCharacter);
	~StateMC_NonCombatJump();

protected:
	//State overrides
	void Start() override;
	void Execute(float) override;

	//State_MainCharacter overrides
	virtual void MoveForward(float);
	virtual void MoveRight(float);
	virtual void TurnRate(float) override;
	virtual void LookUpRate(float) override;
	virtual void Jump();
	//virtual void CollideFeet();

	//Internal functions
	void ApplyGravity(float DeltaTime);

	//Internal variables
	float gravityAccumulation = 0;
	float upwardsVelocityAccumulation = 0;
	float JumpStartedTime = 0;
	float JumpElapsedTime = 0;
};
