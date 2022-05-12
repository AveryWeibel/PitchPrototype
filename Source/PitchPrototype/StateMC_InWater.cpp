// Fill out your copyright notice in the Description page of Project Settings.

//SETTINGS IN VISUAL STUDIO 2022
//Tools>Options>Text Editor>{Language}>Code Style>Formatting>"Choose When I paste, Indent, but do not format"

#include "StateMC_InWater.h"
#include "MainCharacter.h"
#include "CustomDefines.h"
#include "PhysicsEngine/PhysicsConstraintTemplate.h"
DEFINE_LOG_CATEGORY(Log171InWater);

StateMC_InWater::StateMC_InWater(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	//Add new entry to StateName in State.h
	stateName = TidesStateName::InWater;
}

StateMC_InWater::~StateMC_InWater()
{
}

void StateMC_InWater::Start()
{
	UE_LOG(Log171InWater, Log, TEXT("Enter State StateMC_InWater"));
	if(mainCharacter)
	{
		groundTraceParams.AddIgnoredActor(mainCharacter);
	}
	StoredStepHeight = mainCharacter->StepUpHeight;
	mainCharacter->StepUpHeight -= 10;

	TargetFloatHeight = mainCharacter->bodyCollider->GetComponentLocation().Z;
}

void StateMC_InWater::Execute(float DeltaTime)
{
	//Setup moveVector	

	//Position the camera
	MoveCameraUnLocked(DeltaTime);

	//Rotate model towards the movement vector
	RotateCharacterModel(DeltaTime, mainCharacter->horizontalVelocity, mainCharacter->modelTurningRate);
	
	MoveCharacter(DeltaTime, mainCharacter->WaterMovementMultiplier, true, BouyantGravity);

	//Apply moveVector
	BouyantGravity = TargetFloatHeight - mainCharacter->bodyCollider->GetComponentLocation().Z;
	//*movementVector = FVector::ZeroVector;
	//SetPhysicsLinearVelocity(FVector(0, 0, 0));

	if(IsGrounded)
	{
		mainCharacter->StepUpHeight = StoredStepHeight;
		RequestStateChange(TidesStateName::NonCombatMove);
	}
}

void StateMC_InWater::MoveForward(float Value)
{
	GetForwardInput(Value);
}

void StateMC_InWater::MoveRight(float Value)
{
	GetRightInput(Value);
}

void StateMC_InWater::TurnRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnX [%f]"), Value);
	AddCameraOrbitYaw(Value);
}

void StateMC_InWater::LookUpRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnY [%f]"), Value);
	AddCameraOrbitPitch(Value);
}


void StateMC_InWater::BeginOverlapFeet(AActor& OtherActor)
{
	if (!OtherActor.Tags.Contains("Ocean"))
	{
		State_MainCharacter::BeginOverlapFeet( OtherActor);
		UE_LOG(Log171InWater, Log, TEXT("Enter Landscape from Water"));
		mainCharacter->StepUpHeight = StoredStepHeight;
		RequestStateChange(TidesStateName::NonCombatMove);
	}
}

void StateMC_InWater::Die()
{
	State_MainCharacter::Die();
	mainCharacter->StepUpHeight = StoredStepHeight;
	RequestStateChange(TidesStateName::Dead);
}

void StateMC_InWater::ExitWater()
{
	State_MainCharacter::ExitWater();
}

