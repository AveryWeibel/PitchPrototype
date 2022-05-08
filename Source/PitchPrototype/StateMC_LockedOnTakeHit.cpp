// Fill out your copyright notice in the Description page of Project Settings.

//SETTINGS IN VISUAL STUDIO 2022
//Tools>Options>Text Editor>{Language}>Code Style>Formatting>"Choose When I paste, Indent, but do not format"

#include "StateMC_LockedOnTakeHit.h"
#include "MainCharacter.h"
#include "CustomDefines.h"

StateMC_LockedOnTakeHit::StateMC_LockedOnTakeHit(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	//Add new entry to StateName in State.h
	stateName = TidesStateName::LockedOnTakeHit;
}

StateMC_LockedOnTakeHit::~StateMC_LockedOnTakeHit()
{
}

void StateMC_LockedOnTakeHit::Start()
{
	UE_LOG(LogTemp, Log, TEXT("Enter State StateMC_LockedOnTakeHit"));
}

void StateMC_LockedOnTakeHit::Execute(float DeltaTime)
{
	//Update animation variables
	mainCharacter->Animator->SetLookAtTarget(mainCharacter->lockedObject->GetActorLocation());
	mainCharacter->Animator->SetControlDirection(*HorizontalDirVector);
	
	//Move camera to look at target
	FVector dirToTarget = mainCharacter->lockedObject->GetActorLocation() - mainCharacter->GetActorLocation();
	dirToTarget.Z = 0;
	
	MoveCameraLocked(DeltaTime, dirToTarget);
	
	//Rotate model towards the locked target
	RotateCharacterModel(DeltaTime, dirToTarget, mainCharacter->modelTurningRate);

	//Move the character
	MoveCharacter(DeltaTime);

	//Ensure collision does not rotate
	mainCharacter->feetCollider->SetWorldRotation(FRotator(0, 0, 0));
}

void StateMC_LockedOnTakeHit::AnimEnd()
{
	State_MainCharacter::AnimEnd();
	RequestStateChange(TidesStateName::LockedOnMove);
}

void StateMC_LockedOnTakeHit::MoveForward(float Value)
{
	GetForwardInput(Value);
}

void StateMC_LockedOnTakeHit::MoveRight(float Value)
{
	GetRightInput(Value);
}
