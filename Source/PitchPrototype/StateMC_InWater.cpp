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
	mainCharacter->feetCollider->SetConstraintMode(EDOFMode::XYPlane);
	mainCharacter->feetCollider->SetEnableGravity(false);
	mainCharacter->feetCollider->SetSimulatePhysics(false);
	mainCharacter->feetCollider->SetPhysicsLinearVelocity(FVector(0, 0, 0));
}

void StateMC_InWater::Execute(float DeltaTime)
{
	//UE_LOG(LogTemp, Log, TEXT("Execute State InWater"));
	//Setup moveVector	

	//Apply moveVector
	MoveCharacter(DeltaTime, false);

	//Position the camera
	MoveCameraUnLocked(DeltaTime);

	//Rotate model towards the movement vector
	if (movementVector->Size() > 0)
	{
		mainCharacter->Mesh->SetWorldRotation(FMath::Lerp(mainCharacter->Mesh->GetComponentRotation(),  FRotator(mainCharacter->Mesh->GetComponentRotation().Pitch,  movementVector->Rotation().Yaw, mainCharacter->Mesh->GetComponentRotation().Roll), FMath::Clamp( mainCharacter->modelTurningRate * DeltaTime, DeltaTime, mainCharacter->modelTurningRate)));
	}

	*movementVector = FVector::ZeroVector;
	mainCharacter->feetCollider->SetPhysicsLinearVelocity(FVector(0, 0, 0));
	//UE_LOG(Log171InWater, Log, TEXT("VelocityF: %f"), mainCharacter->feetCollider->GetPhysicsLinearVelocity().Size());
	//UE_LOG(Log171InWater, Log, TEXT("VelocityB: %f"), mainCharacter->bodyCollider->GetPhysicsLinearVelocity().Size());
}

void StateMC_InWater::MoveForward(float Value)
{
	FVector direction = mainCharacter->cameraBoom->GetForwardVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce * mainCharacter->WaterMovementMultiplier);
	*movementVector += FVector(direction.X, direction.Y, 0);
}

void StateMC_InWater::MoveRight(float Value)
{
	FVector direction = mainCharacter->cameraBoom->GetRightVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce * mainCharacter->WaterMovementMultiplier);
	*movementVector += FVector(direction.X, direction.Y, 0);
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
	if (OtherActor.Tags.Contains("Landscape"))
	{
		State_MainCharacter::BeginOverlapFeet( OtherActor);
		UE_LOG(Log171InWater, Log, TEXT("Enter Landscape from Water"));
		mainCharacter->feetCollider->SetConstraintMode(EDOFMode::None);
		mainCharacter->feetCollider->SetEnableGravity(true);
		mainCharacter->feetCollider->SetSimulatePhysics(true);
		RequestStateChange(TidesStateName::NonCombatMove);
	}
}

void StateMC_InWater::Die()
{
	State_MainCharacter::Die();
	mainCharacter->feetCollider->SetSimulatePhysics(false);
	RequestStateChange(TidesStateName::Dead);
}

void StateMC_InWater::ExitWater()
{
	// State_MainCharacter::ExitWater();
	// mainCharacter->feetCollider->SetConstraintMode(EDOFMode::None);
	// mainCharacter->feetCollider->SetEnableGravity(true);
	// RequestStateChange(TidesStateName::NonCombatMove);
}

