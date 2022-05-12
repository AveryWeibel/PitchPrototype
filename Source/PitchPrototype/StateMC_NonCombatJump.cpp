// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMC_NonCombatJump.h"
#include "MainCharacter.h"
#include "CustomDefines.h"

DEFINE_LOG_CATEGORY(Log171NonCombatJump);

StateMC_NonCombatJump::StateMC_NonCombatJump(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	//Add new entry to StateName in State.h
	stateName = TidesStateName::NonCombatJump;
}

StateMC_NonCombatJump::~StateMC_NonCombatJump()
{

}

void StateMC_NonCombatJump::Start()
{
	UE_LOG(Log171NonCombatJump, Log, TEXT("Enter State StateMC_NonCombatJump"));
	//Initial jump functionality
	JumpStartedTime = mainCharacter->GetWorld()->TimeSeconds;
	if(mainCharacter)
	{
		groundTraceParams.AddIgnoredActor(mainCharacter);
	}
}

void StateMC_NonCombatJump::Execute(float DeltaTime)
{	
	//Track time
	JumpElapsedTime = mainCharacter->GetWorld()->TimeSeconds - JumpStartedTime;
	
	//Setup moveVector
	if (JumpElapsedTime < mainCharacter->MaxJumpAccelTime)
	{
		//upwardsVelocityAccumulation += mainCharacter->jumpAccel * DeltaTime;
		VerticalVector += mainCharacter->jumpAccel * DeltaTime;
	}
	//Change to inair state once we start falling
	else if (VerticalVector <= 0) {
		gravityAccumulation = 0;
		upwardsVelocityAccumulation = 0;
		UE_LOG(Log171NonCombatJump, Log, TEXT("Jump time: %f"), JumpElapsedTime);
		JumpElapsedTime = 0;
		JumpStartedTime = 0;
		RequestStateChange(TidesStateName::NonCombatInAir);
	}

	//ApplyGravity(DeltaTime);
	
	//Rotate model towards the movement vector
	RotateCharacterModel(DeltaTime, mainCharacter->horizontalVelocity, mainCharacter->modelTurningRate);
	
	//Apply moveVector
	MoveCharacter(DeltaTime, 1, true, mainCharacter->risingGravityAmount);

	//Move camera
	MoveCameraUnLocked(DeltaTime);
	
	
}

void StateMC_NonCombatJump::Jump()
{
	State_MainCharacter::Jump();

}

void StateMC_NonCombatJump::MoveForward(float Value)
{
	GetForwardInput(Value);
}

void StateMC_NonCombatJump::MoveRight(float Value)
{

	GetRightInput(Value);
}

void StateMC_NonCombatJump::TurnRate(float Value)
{
	AddCameraOrbitYaw(Value);
}

void StateMC_NonCombatJump::LookUpRate(float Value)
{
	AddCameraOrbitPitch(Value);
}

void StateMC_NonCombatJump::ApplyGravity(float DeltaTime)
{
	if (FMath::Abs(VerticalVector) < mainCharacter->maxFallingSpeed)
	{
		gravityAccumulation -= mainCharacter->risingGravityAmount;
		VerticalVector += gravityAccumulation * DeltaTime;
	}
}
