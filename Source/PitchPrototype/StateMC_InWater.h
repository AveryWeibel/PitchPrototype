// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_MainCharacter.h"

///	<summary>
/// Default Summary
///	</summary>
DECLARE_LOG_CATEGORY_EXTERN(Log171InWater, Log, All);

class PITCHPROTOTYPE_API StateMC_InWater : public State_MainCharacter
{
public:
	StateMC_InWater(AMainCharacter* mainCharacter);
	~StateMC_InWater();

protected:
	//State overrides
	void Start() override;
	void Execute(float) override;

	//State_MainCharacter overrides
	virtual void MoveForward(float) override;
	virtual void MoveRight(float) override;
	virtual  void LookUpRate(float) override;
	virtual void TurnRate(float) override;
	//virtual void Jump() override;
	virtual void BeginOverlapFeet(AActor& OtherActor) override;
	virtual void Die() override;
	virtual void ExitWater() override;

	//Internal functions

	//Internal variables
	float StoredStepHeight;
	float TargetFloatHeight;
	float BouyantGravity = 0;
	float StoredMaxCameraPitch = 0;
};
