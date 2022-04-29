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
	cameraBoomTargetLength = mainCharacter->cameraUnLockedBoomLength;
	*cameraTurnVector = mainCharacter->cameraBoom->GetRelativeRotation();
	RagdollModel();
}

void StateMC_Dead::Execute(float DeltaTime)
{
	//UE_LOG(LogTemp, Log, TEXT("Execute State StateMC_Dead"));
	//Setup moveVector	
	
	ConsumeCameraInput(DeltaTime);

	//Apply moveVector

	//Position the camera
	//Rotate camera to face in same direction as cameraBoom
	cameraRotationLerpTarget = mainCharacter->cameraBoom->GetComponentRotation();
	mainCharacter->mainCamera->SetWorldRotation(FMath::Lerp(mainCharacter->mainCamera->GetComponentRotation(), cameraRotationLerpTarget, mainCharacter->cameraLerpAlpha * DeltaTime));

	//Lerp camera boom length to correct length
	mainCharacter->cameraBoom->TargetArmLength = FMath::Lerp(mainCharacter->cameraBoom->TargetArmLength, cameraBoomTargetLength, mainCharacter->cameraLerpAlpha * DeltaTime);

	//Rotate cameraBoom to face turnvector
	cameraBoomRotationLerpTarget = *cameraTurnVector;
	mainCharacter->cameraBoom->SetWorldRotation(FMath::Lerp(mainCharacter->cameraBoom->GetRelativeRotation(), cameraBoomRotationLerpTarget,  FMath::Clamp(mainCharacter->cameraLerpAlpha * 35 * DeltaTime, DeltaTime, mainCharacter->cameraLerpAlpha)));	
	
	mainCharacter->cameraBoom->SetRelativeLocation(
		FVector (
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().X, mainCharacter->cameraUnLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().X, mainCharacter->cameraLerpAlpha * DeltaTime),
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Y, mainCharacter->cameraUnLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().Y, mainCharacter->cameraLerpAlpha * DeltaTime),
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Z, mainCharacter->cameraUnLockedHeight, mainCharacter->cameraLerpAlpha * DeltaTime)
		)
	);
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

