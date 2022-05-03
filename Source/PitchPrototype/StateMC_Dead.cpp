// Fill out your copyright notice in the Description page of Project Settings.

//SETTINGS IN VISUAL STUDIO 2022
//Tools>Options>Text Editor>{Language}>Code Style>Formatting>"Choose When I paste, Indent, but do not format"

#include "StateMC_Dead.h"
#include "MainCharacter.h"
#include "CustomDefines.h"

StateMC_Dead::StateMC_Dead(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	//Add new entry to StateName in State.h
	stateName = TidesStateName::Dead;
}

StateMC_Dead::~StateMC_Dead()
{
}

void StateMC_Dead::Start()
{
	UE_LOG(LogTemp, Log, TEXT("Enter State StateMC_Dead"));
	*cameraTurnVector = mainCharacter->cameraBoom->GetRelativeRotation();
	RagdollModel();
}

void StateMC_Dead::Execute(float DeltaTime)
{
	//UE_LOG(LogTemp, Log, TEXT("Execute State StateMC_Dead"));
	//Setup moveVector	

	//Apply moveVector

	//Position the camera
	MoveCameraUnLocked(DeltaTime);
}

void StateMC_Dead::TurnRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnX [%f]"), Value);
	AddCameraOrbitYaw(Value);
}

void StateMC_Dead::LookUpRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnY [%f]"), Value);
	AddCameraOrbitPitch(Value);
}

