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
	mainCharacter->Animator->SetLookAtTarget(mainCharacter->lockedAI->GetActorLocation());
	mainCharacter->Animator->SetControlDirection(FVector(moveFwd, moveRht, 0));

	//UE_LOG(Log171General, Log, TEXT("Fwd: %f, Rht: %f"), FMath::Abs(moveFwd), FMath::Abs(moveRht));

	ConsumeMoveInputs();

	//Move the character
	if (mainCharacter->feetCollider->GetPhysicsLinearVelocity().Size() <= mainCharacter->maximumHorizontalVelocity / 3) {
		//FVector forceDirection(, , 0);
		mainCharacter->feetCollider->AddForce(*movementVector);
		//mainCharacter->AddActorWorldOffset(*movementVector / 500000);
	}
	
	//Lerp cameraBoom to rotate between player and target
	//2D so the camera doesn't tilt with distance
	FVector dirToTarget = mainCharacter->lockedAI->GetActorLocation() - mainCharacter->GetActorLocation();
	dirToTarget.Z = 0;
	//Lerp camera to face target
	cameraRotationLerpTarget = (mainCharacter->lockedAI->GetActorLocation() - mainCharacter->mainCamera->GetComponentLocation()).Rotation();
	mainCharacter->mainCamera->SetWorldRotation(FMath::Lerp(mainCharacter->mainCamera->GetComponentRotation(), cameraRotationLerpTarget, mainCharacter->cameraLerpAlpha * DeltaTime));

	//Lerp cameraBoom to rotate between player and target
	//2D so the camera doesn't tilt with distance
	cameraBoomRotationLerpTarget = (dirToTarget).Rotation();
	mainCharacter->cameraBoom->SetWorldRotation(FMath::Lerp(mainCharacter->cameraBoom->GetComponentRotation(), cameraBoomRotationLerpTarget, FMath::Clamp(mainCharacter->cameraLerpAlpha * 35 * DeltaTime, DeltaTime, mainCharacter->cameraLerpAlpha)));	

	
	//Rotate model towards the locked target
	if (movementVector->Size() > 0) {
		mainCharacter->Mesh->SetWorldRotation(FMath::Lerp(mainCharacter->Mesh->GetRelativeRotation(),  dirToTarget.Rotation(), FMath::Clamp( 4 * DeltaTime, DeltaTime, 4.0f)));
	}

	//Ensure collision does not rotate
	mainCharacter->feetCollider->SetWorldRotation(FRotator(0, 0, 0));
	*movementVector = FVector::ZeroVector;
}

void StateMC_LockedOnTakeHit::AnimEnd()
{
	State_MainCharacter::AnimEnd();
	RequestStateChange(TidesStateName::LockedOnMove);
}

void StateMC_LockedOnTakeHit::MoveForward(float Value)
{
	moveFwd = Value;
	//if(Value != 0)
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CharacterVelocity[X: %f, Y: %f, Z: %f]"), mainCharacter->feetCollider->GetPhysicsLinearVelocity().X, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Y, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Z);
	

	FVector direction = mainCharacter->mainCamera->GetForwardVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce);
	*movementVector += FVector(direction.X, direction.Y, moveZ);
	//moveX = Value * mainCharacter->mainCamera->GetForwardVector().X * mainCharacter->accelerationForce;
}

void StateMC_LockedOnTakeHit::MoveRight(float Value)
{
	moveRht = Value;

	//if (Value != 0)
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CharacterVelocity[X: %f, Y: %f, Z: %f]"), mainCharacter->feetCollider->GetPhysicsLinearVelocity().X, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Y, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Z);

	//moveY = Value * mainCharacter->accelerationForce;
	FVector direction = mainCharacter->mainCamera->GetRightVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce);
	*movementVector += FVector(direction.X, direction.Y, moveZ);
}
