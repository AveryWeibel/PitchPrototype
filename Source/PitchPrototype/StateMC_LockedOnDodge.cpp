// Fill out your copyright notice in the Description page of Project Settings.

//SETTINGS IN VISUAL STUDIO 2022
//Tools>Options>Text Editor>{Language}>Code Style>Formatting>"Choose When I paste, Indent, but do not format"

#include "StateMC_LockedOnDodge.h"
#include "MainCharacter.h"
#include "CustomDefines.h"
#include "StateMC_NonCombatMove.h"

StateMC_LockedOnDodge::StateMC_LockedOnDodge(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	//Add new entry to StateName in State.h
	stateName = TidesStateName::LockedOnDodging;
}

StateMC_LockedOnDodge::~StateMC_LockedOnDodge()
{
}

void StateMC_LockedOnDodge::Start()
{
	DodgeStartedTime = mainCharacter->GetWorld()->GetTimeSeconds();
	//DodgeDirection = FVector(mainCharacter->currentPhysicsLinearVelocity.X, mainCharacter->currentPhysicsLinearVelocity.Y, 0);
	if(mainCharacter)
	{
		groundTraceParams.AddIgnoredActor(mainCharacter);
		//GroundTraceResponseParams.DefaultResponseParam.
	}
}

void StateMC_LockedOnDodge::Execute(float DeltaTime)
{
	//UE_LOG(LogTemp, Log, TEXT("Execute State StateMC_LockedOnDodge"));
	//Update timer
	DodgeElapsedTime = mainCharacter->GetWorld()->GetTimeSeconds() - DodgeStartedTime;
	
	//Setup moveVector

	//Move the camera
	FVector dirToTarget = mainCharacter->lockedObject->GetActorLocation() - mainCharacter->GetActorLocation();
	//2D so the camera doesn't tilt with distance
	dirToTarget.Z = 0;
	MoveCameraLocked(DeltaTime, dirToTarget, 0.35f);

	//Move the character for dodge
	MoveCharacter(DeltaTime, mainCharacter->dodgeSpeed, true, mainCharacter->fallingGravityAmount, false);
	UE_LOG(Log171General, Log, TEXT("StoredDIr: %f, %f"), StoredDodgeDirection.X, StoredDodgeDirection.Y);

	//Rotate model towards the locked target
	RotateCharacterModel(DeltaTime, dirToTarget, mainCharacter->modelTurningRate);
	
	//Check if dodge time has elapsed
	if(DodgeElapsedTime >= mainCharacter->dodgeLength)
	{
		StoredDodgeDirection = FVector2D::ZeroVector;
		mainCharacter->DodgeEndedTime = mainCharacter->GetWorld()->GetTimeSeconds();
		UE_LOG(Log171General, Log, TEXT("From Dodge: %f"), mainCharacter->DodgeEndedTime);
		RequestStateChange(TidesStateName::LockedOnMove);
	}
}

void StateMC_LockedOnDodge::MoveForward(float Value)
{
	GetForwardInput(Value);
}

void StateMC_LockedOnDodge::MoveRight(float Value)
{
	GetRightInput(Value);
}

void StateMC_LockedOnDodge::TakeHit()
{
	State_MainCharacter::TakeHit();
	const FString varName{"COUNT_playerDodges"};
	
	mainCharacter->NativeSetDialogueInt(varName, mainCharacter->NativeGetDialogueInt(varName) + 1);
	UE_LOG(Log171General, Log, TEXT("Updated %s to %d"), *varName, mainCharacter->NativeGetDialogueInt(varName));
}

