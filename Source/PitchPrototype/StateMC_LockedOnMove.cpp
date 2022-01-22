// Fill out your copyright notice in the Description page of Project Settings.

//SETTINGS IN VISUAL STUDIO 2022
//Tools>Options>Text Editor>{Language}>Code Style>Formatting>"Choose When I paste, Indent, but do not format"

#include "StateMC_LockedOnMove.h"
#include "MainCharacter.h"
#include "CustomDefines.h"

DEFINE_LOG_CATEGORY(Log171LockedOnMove);

StateMC_LockedOnMove::StateMC_LockedOnMove(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	//Add new entry to StateName in State.h
	stateName = StateName::LockedOnMove;
}

StateMC_LockedOnMove::~StateMC_LockedOnMove()
{
	
}

void StateMC_LockedOnMove::Start()
{
	UE_LOG(LogTemp, Log, TEXT("Enter State StateMC_LockedOnMove"));
}

void StateMC_LockedOnMove::Execute(float DeltaTime)
{
	//Apply skeletal forces
	float tiltAmount = mainCharacter->Animator->GetTiltAmount();
	mainCharacter->Animator->SetTiltAmount(FMath::Lerp(tiltAmount, FMath::Abs(moveFwd) + FMath::Abs(moveRht), .01f));


	//UE_LOG(Log171General, Log, TEXT("Fwd: %f, Rht: %f"), FMath::Abs(moveFwd), FMath::Abs(moveRht));

	ConsumeMoveInputs();
	ConsumeCameraInput();

	//Move the character
	if (mainCharacter->feetCollider->GetPhysicsLinearVelocity().Size() <= mainCharacter->maximumHorizontalVelocity) {
		//FVector forceDirection(, , 0);
		mainCharacter->feetCollider->AddForce(*movementVector);
		//mainCharacter->AddActorWorldOffset(*movementVector / 500000);
	}

	//Move the camera
	mainCharacter->cameraBoom->SetWorldRotation(*cameraTurnVector);

	//Rotate model towards the movement vector
	if (movementVector->Size() > 0) {
		mainCharacter->Mesh->SetWorldRotation(FMath::Lerp(mainCharacter->Mesh->GetRelativeRotation(),  movementVector->Rotation(), 0.04f));

		//float turnDelta = 
		
		//UE_LOG(Log171General, Log, TEXT("MovementDirection X[%f], Y[%f], Z[%f]"), movementVector->X, movementVector->Y, movementVector->Z);
	}

	//Ensure collision does not rotate
	mainCharacter->feetCollider->SetWorldRotation(FRotator(0, 0, 0));
	*movementVector = FVector::ZeroVector;
}

void StateMC_LockedOnMove::MoveForward(float Value)
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

void StateMC_LockedOnMove::MoveRight(float Value)
{
	moveRht = Value;

	//if (Value != 0)
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CharacterVelocity[X: %f, Y: %f, Z: %f]"), mainCharacter->feetCollider->GetPhysicsLinearVelocity().X, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Y, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Z);
	
	mainCharacter->Animator->SetTurnAmount(moveRht);

	//moveY = Value * mainCharacter->accelerationForce;
	FVector direction = mainCharacter->mainCamera->GetRightVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce);
	*movementVector += FVector(direction.X, direction.Y, moveZ);
}

void StateMC_LockedOnMove::LockOn()
{
	UE_LOG(Log171LockedOnMove, Log, TEXT("Locked off of [%s]"), *mainCharacter->lockedAI->GetName());
	mainCharacter->lockedAI = nullptr;
	RequestStateChange(StateName::NonCombatMove);
	
}
