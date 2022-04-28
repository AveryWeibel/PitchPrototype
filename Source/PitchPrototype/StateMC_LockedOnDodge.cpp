// Fill out your copyright notice in the Description page of Project Settings.

//SETTINGS IN VISUAL STUDIO 2022
//Tools>Options>Text Editor>{Language}>Code Style>Formatting>"Choose When I paste, Indent, but do not format"

#include "StateMC_LockedOnDodge.h"
#include "MainCharacter.h"
#include "CustomDefines.h"

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
	DodgeDirection = FVector(mainCharacter->currentPhysicsLinearVelocity.X, mainCharacter->currentPhysicsLinearVelocity.Y, 0);
	cameraBoomTargetLength = mainCharacter->cameraLockedBoomLength;
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
	if(FMath::Abs(DodgeDirection.X) > .01f || FMath::Abs(DodgeDirection.Y) > .01f)
	{
		//UE_LOG(LogTemp, Log, TEXT("(X: %f, Y: %f), DLT: %f"), mainCharacter->currentPhysicsLinearVelocity.X, mainCharacter->currentPhysicsLinearVelocity.Y, DeltaTime);
		DodgeDirection.Normalize();
		DodgeMoveVelocity += DodgeDirection * (mainCharacter->dodgeSpeed / DodgeDamping) * DeltaTime;
		mainCharacter->AddActorWorldOffset(DodgeMoveVelocity * DeltaTime);
	}

	//Check if dodge time has elapsed
	if(DodgeElapsedTime >= mainCharacter->dodgeLength)
	{
		DodgeMoveVelocity = FVector::ZeroVector;
		DodgeDamping = 1;
		RequestStateChange(TidesStateName::LockedOnMove);
	}

	DodgeDirection = FVector::ZeroVector;
	DodgeDamping = FMath::Clamp(DodgeDamping - 0.025f, 0.2f, 1.0f);
	//Apply moveVector
}

void StateMC_LockedOnDodge::MoveForward(float Value)
{
	//if(Value != 0)
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CharacterVelocity[X: %f, Y: %f, Z: %f]"), mainCharacter->feetCollider->GetPhysicsLinearVelocity().X, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Y, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Z);
	

	FVector direction = mainCharacter->mainCamera->GetForwardVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= Value;

	FVector dirVector = FVector(direction.X, direction.Y, 0);

	//DodgeDamping = FMath::Clamp(FVector::DotProduct(DodgeDirection, DodgeDirection + dirVector), 0.2f, 1.0f);
	DodgeDirection += dirVector;
	//moveX = Value * mainCharacter->mainCamera->GetForwardVector().X * mainCharacter->accelerationForce;
}

void StateMC_LockedOnDodge::MoveRight(float Value)
{
	
	//if (Value != 0)
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CharacterVelocity[X: %f, Y: %f, Z: %f]"), mainCharacter->feetCollider->GetPhysicsLinearVelocity().X, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Y, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Z);

	//moveY = Value * mainCharacter->accelerationForce;
	FVector direction = mainCharacter->mainCamera->GetRightVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= Value;

	FVector dirVector = FVector(direction.X, direction.Y, 0);

	//DodgeDamping = FMath::Clamp(FVector::DotProduct(DodgeDirection, DodgeDirection + dirVector), 0.2f, 1.0f);
	
	DodgeDirection += dirVector;
}

void StateMC_LockedOnDodge::TakeHit()
{
	State_MainCharacter::TakeHit();
	const FString varName{"COUNT_playerDodges"};
	
	mainCharacter->NativeSetDialogueInt(varName, mainCharacter->NativeGetDialogueInt(varName) + 1);
	UE_LOG(Log171General, Log, TEXT("Updated %s to %d"), *varName, mainCharacter->NativeGetDialogueInt(varName));
}

