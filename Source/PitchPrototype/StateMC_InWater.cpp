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
	UE_LOG(LogTemp, Log, TEXT("Enter State StateMC_InWater"));
	mainCharacter->feetCollider->SetConstraintMode(EDOFMode::XYPlane);
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
}

void StateMC_InWater::MoveForward(float Value)
{
	FVector direction = mainCharacter->cameraBoom->GetForwardVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce);
	*movementVector += FVector(direction.X, direction.Y, 0);
}

void StateMC_InWater::MoveRight(float Value)
{
	FVector direction = mainCharacter->cameraBoom->GetRightVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce);
	*movementVector += FVector(direction.X, direction.Y, 0);
}


void StateMC_InWater::BeginOverlapFeet()
{
	State_MainCharacter::BeginOverlapFeet();
	mainCharacter->feetCollider->SetConstraintMode(EDOFMode::None);
	RequestStateChange(TidesStateName::NonCombatMove);
}

