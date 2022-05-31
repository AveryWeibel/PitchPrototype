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
	//virtual void Jump() override;
	//virtual void CollideFeet();
	virtual void LockOn() override;
	virtual void TurnRate(float) override;
	virtual void LookUpRate(float) override;
	virtual void DoAttack() override;
	virtual void TakeHit() override;
	virtual void Die() override;
	virtual void Parry() override;
	virtual void Dodge() override;
	virtual void Interact() override;
	virtual void Sheathe() override;

	virtual void EndOverlapAI();

	//Internal functions

	//Internal variables
	float ParryLerpTarget;
	UPROPERTY()
	FVector dirToTarget;
	bool AnimatingArms = false;
	bool ArmsRaised = false;
};
