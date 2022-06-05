// Fill out your copyright notice in the Description page of Project Settings.

//SETTINGS IN VISUAL STUDIO 2022
//Tools>Options>Text Editor>{Language}>Code Style>Formatting>"Choose When I paste, Indent, but do not format"

#include "StateMC_Intro.h"
#include "MainCharacter.h"
#include "CustomDefines.h"

DEFINE_LOG_CATEGORY(Log171Intro);

StateMC_Intro::StateMC_Intro(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	//Add new entry to StateName in State.h
	stateName = TidesStateName::Intro;
}

StateMC_Intro::~StateMC_Intro()
{
	
}

void StateMC_Intro::Start()
{
	UE_LOG(LogTemp, Log, TEXT("Enter State StateMC_Intro"));
	IntroStartTime = mainCharacter->GetWorld()->GetTimeSeconds();
}

void StateMC_Intro::Execute(float DeltaTime)
{
	IntroElapsedTime = mainCharacter->GetWorld()->GetTimeSeconds() - IntroStartTime;

	if(IntroElapsedTime > mainCharacter->IntroWaitTime && !IntroPlaying)
	{
		StartIntro();
	}

	UE_LOG(Log171Intro, Log, TEXT("MontageTime: %f"), mainCharacter->Animator->GetMontageTime());
	
	//UE_LOG(LogTemp, Log, TEXT("Execute State StateMC_Intro"));
	MoveCameraUnLocked(DeltaTime);
	
	//Setup moveVector	

	//Apply moveVector
}

void StateMC_Intro::Jump()
{
	State_MainCharacter::Jump();
	StartIntro();
}

void StateMC_Intro::TurnRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnX [%f]"), Value);
	AddCameraOrbitYaw(Value);
}

void StateMC_Intro::LookUpRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnY [%f]"), Value);
	AddCameraOrbitPitch(Value);
}

void StateMC_Intro::EndIntroAnim()
{
	State_MainCharacter::EndIntroAnim();
	RequestStateChange(NonCombatMove);
}

void StateMC_Intro::MoveForward(float X)
{
	State_MainCharacter::MoveForward(X);
	if(X != 0)
	{
		StartIntro();
	}
}

void StateMC_Intro::MoveRight(float X)
{
	State_MainCharacter::MoveRight(X);
	if(X != 0)
	{
		StartIntro();
	}
}

void StateMC_Intro::StartIntro()
{
	if(IntroPlaying) { return; }
	
	IntroPlaying = true;
	StartIntroMontage();
}



