// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_MainCharacter.h"

DECLARE_LOG_CATEGORY_EXTERN(Log171NonCombatMove, Log, All);

///	<summary>
/// This state handles standard Locomotion when on the ground
///	</summary>
class PITCHPROTOTYPE_API StateMC_NonCombatMove : public State_MainCharacter
{
public:
	StateMC_NonCombatMove(AMainCharacter*);
	~StateMC_NonCombatMove();


protected:
	//State overrides
	void Start() override;
	void Execute(float) override;

	//State_MainCharacter overrides
	void MoveForward(float) override;
	void MoveRight(float) override;
	void TurnRate(float) override;
	void LookUpRate(float) override;
	void Jump() override;
	void LockOn() override;
	void BeginOverlapFeet() override;
	void EndOverlapFeet() override;
};
