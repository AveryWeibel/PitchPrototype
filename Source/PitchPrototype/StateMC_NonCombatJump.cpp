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
	upwardsVelocityAccumulation += mainCharacter->jumpAccel;
	*movementVector = storedMovement;
	*movementVector += FVector(0, 0, upwardsVelocityAccumulation*10);
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
		upwardsVelocityAccumulation += mainCharacter->jumpAccel;
		*movementVector += FVector(0, 0, upwardsVelocityAccumulation);
	}
	ApplyGravity();
	
	//Apply moveVector
	MoveCharacter(DeltaTime, true, false);

	//Move camera
	MoveCameraUnLocked(DeltaTime);

	//Change to inair state once we start falling
	if (movementVector->Z <= 0) {
		gravityAccumulation = 0;
		upwardsVelocityAccumulation = 0;
		JumpElapsedTime = 0;
		JumpStartedTime = 0;
		RequestStateChange(TidesStateName::NonCombatInAir);
	}

	//Rotate model towards the movement vector
	if (movementVector->Size() > 0)
	{
		mainCharacter->Mesh->SetWorldRotation(FMath::Lerp(mainCharacter->Mesh->GetComponentRotation(),  FRotator(mainCharacter->Mesh->GetComponentRotation().Pitch,  movementVector->Rotation().Yaw, mainCharacter->Mesh->GetComponentRotation().Roll), FMath::Clamp( mainCharacter->modelTurningRate * DeltaTime, DeltaTime, mainCharacter->modelTurningRate)));
	}

	mainCharacter->feetCollider->SetWorldRotation(FRotator(0, 0, 0));
	*movementVector = FVector::ZeroVector;
}

void StateMC_NonCombatJump::Jump()
{
	State_MainCharacter::Jump();

}

void StateMC_NonCombatJump::MoveForward(float Value)
{

	FVector direction = mainCharacter->cameraBoom->GetForwardVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce * mainCharacter->jumpDirectionalMultiplier);
	*movementVector += FVector(direction.X, direction.Y, 0);
}

void StateMC_NonCombatJump::MoveRight(float Value)
{

	//moveY = Value * mainCharacter->accelerationForce;
	FVector direction = mainCharacter->cameraBoom->GetRightVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce * mainCharacter->jumpDirectionalMultiplier);
	*movementVector += FVector(direction.X, direction.Y, 0);
}

void StateMC_NonCombatJump::TurnRate(float Value)
{
	AddCameraOrbitYaw(Value);
}

void StateMC_NonCombatJump::LookUpRate(float Value)
{
	AddCameraOrbitPitch(Value);
}

void StateMC_NonCombatJump::ApplyGravity()
{
	if (FMath::Abs(movementVector->Z) < mainCharacter->maxFallingSpeed)
	{
		gravityAccumulation -= mainCharacter->risingGravityAmount;
		(*movementVector).Z += gravityAccumulation;
	}
}
