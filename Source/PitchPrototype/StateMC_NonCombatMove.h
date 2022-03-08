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
	virtual void MoveForward(float) override;
	virtual void MoveRight(float) override;
	virtual void TurnRate(float) override;
	virtual void LookUpRate(float) override;
	virtual void Jump() override;
	virtual void LockOn() override;
	virtual void Die() override;
	virtual void BeginOverlapFeet() override;
	virtual void EndOverlapFeet() override;
};
