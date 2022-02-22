// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_MainCharacter.h"

///	<summary>
/// Default Summary
///	</summary>
class PITCHPROTOTYPE_API StateMC_LockedOnDodge : public State_MainCharacter
{
public:
	StateMC_LockedOnDodge(AMainCharacter* mainCharacter);
	~StateMC_LockedOnDodge();

	

protected:
	//State overrides
	void Start() override;
	void Execute(float) override;

	//State_MainCharacter overrides
	virtual void MoveForward(float) override;
	virtual void MoveRight(float) override;
	virtual void TakeHit() override;
	//virtual void Jump() override;
	//virtual void CollideFeet() override;

	//Internal functions

	//Internal variables
	float DodgeStartedTime;
	float DodgeElapsedTime;
	float DodgeDamping;
	FVector DodgeMoveVelocity;
	FVector DodgeDirection;
};
