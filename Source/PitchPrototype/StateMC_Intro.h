// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_MainCharacter.h"

///	<summary>
/// Default Summary
///	</summary>
DECLARE_LOG_CATEGORY_EXTERN(Log171Intro, Log, All);

class PITCHPROTOTYPE_API StateMC_Intro : public State_MainCharacter
{
public:
	StateMC_Intro(AMainCharacter* mainCharacter);
	~StateMC_Intro();

protected:
	//State overrides
	void Start() override;
	void Execute(float) override;

	//State_MainCharacter overrides
	//virtual void MoveForward(float) override;
	//virtual void MoveRight(float) override;
	virtual void Jump() override;
	//virtual void CollideFeet() override;
	virtual void TurnRate(float) override;
	virtual void LookUpRate(float) override;
	virtual void EndIntroAnim() override;
	virtual void MoveForward(float) override;
	virtual void MoveRight(float) override;

	//Internal functions
	void StartIntro();

	//Internal variables
	bool IntroPlaying = false;
	float IntroStartTime = 0;
	float IntroElapsedTime = 0;
};
