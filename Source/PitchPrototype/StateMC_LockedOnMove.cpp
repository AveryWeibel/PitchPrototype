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
	stateName = TidesStateName::LockedOnMove;
}

StateMC_LockedOnMove::~StateMC_LockedOnMove()
{
	
}

void StateMC_LockedOnMove::Start()
{
	UE_LOG(LogTemp, Log, TEXT("Enter State StateMC_LockedOnMove"));
	cameraBoomTargetLength = mainCharacter->cameraLockedBoomLength;
}

void StateMC_LockedOnMove::Execute(float DeltaTime)
{
	
	
	//Update animation variables
	mainCharacter->Animator->SetLookAtTarget(mainCharacter->lockedAI->GetActorLocation());

	mainCharacter->Animator->SetControlDirection( FMath::Lerp( mainCharacter->Animator->GetControlDirection(), FVector(moveFwd, moveRht, 0), 0.2f) );

	if(mainCharacter->Animator->GetParryAlpha() >= .95)
	{
		ParryLerpTarget = 0;
	}

	mainCharacter->Animator->SetParryIKTarget(mainCharacter->lockedAI->Weapon->GetActorLocation());
	mainCharacter->Animator->SetParryAlpha(FMath::Lerp(mainCharacter->Animator->GetParryAlpha(), ParryLerpTarget, 10 * DeltaTime));


	
	//UE_LOG(Log171General, Log, TEXT("Fwd: %f, Rht: %f"), FMath::Abs(moveFwd), FMath::Abs(moveRht));

	ConsumeMoveInputs();

	//Move the character
	if (mainCharacter->feetCollider->GetPhysicsLinearVelocity().Size() <= mainCharacter->maximumHorizontalVelocity / 3) {
		//FVector forceDirection(, , 0);
		mainCharacter->feetCollider->AddForce(*movementVector);
		//mainCharacter->AddActorWorldOffset(*movementVector / 500000);
	}
	
	//Move the camera
	FVector dirToTarget = mainCharacter->lockedAI->GetActorLocation() - mainCharacter->GetActorLocation();
	//2D so the camera doesn't tilt with distance
	dirToTarget.Z = 0;
	MoveCameraLocked(DeltaTime, dirToTarget);

	//Rotate model towards the locked target
	if (movementVector->Size() > 0) {
		mainCharacter->Mesh->SetWorldRotation(FMath::Lerp(mainCharacter->Mesh->GetRelativeRotation(),  dirToTarget.Rotation(), FMath::Clamp( 4 * DeltaTime, DeltaTime, 4.0f)));

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
	storedMovement = *movementVector;
	//moveX = Value * mainCharacter->mainCamera->GetForwardVector().X * mainCharacter->accelerationForce;
}

void StateMC_LockedOnMove::MoveRight(float Value)
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
	storedMovement = *movementVector;
}

void StateMC_LockedOnMove::LockOn()
{
	UE_LOG(Log171LockedOnMove, Log, TEXT("Locked off of [%s]"), *mainCharacter->lockedAI->GetName());
	mainCharacter->lockedAI->PlayerUnLock();
	//*cameraTurnVector = mainCharacter->cameraBoom->GetComponentRotation();
	mainCharacter->lockedAI = nullptr;
	
	RequestStateChange(TidesStateName::NonCombatMove);
	
}

void StateMC_LockedOnMove::TurnRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnX [%f]"), Value);
	//cameraInputX += Value;
}

void StateMC_LockedOnMove::LookUpRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnY [%f]"), Value);
	//cameraInputY += Value;
}

void StateMC_LockedOnMove::DoAttack()
{
	State_MainCharacter::DoAttack();
	ParryLerpTarget = 0;
	mainCharacter->Animator->SetParryAlpha(0);
	RequestStateChange(TidesStateName::SwordAttack);
}

void StateMC_LockedOnMove::TakeHit()
{
	State_MainCharacter::TakeHit();
	ParryLerpTarget = 0;
	mainCharacter->Animator->SetParryAlpha(0);
	RequestStateChange(TidesStateName::LockedOnTakeHit);
}

void StateMC_LockedOnMove::Parry()
{
	State_MainCharacter::Parry();
	
	if(mainCharacter->Animator->GetParryAlpha() <= .05f) {
		mainCharacter->Animator->SetParryIKTarget(mainCharacter->lockedAI->Weapon->parryTarget);
		ParryLerpTarget = 1;
		if(mainCharacter->lockedAI->Animator->GetParryable() && mainCharacter->GetDistanceTo(mainCharacter->lockedAI) < mainCharacter->parryDistance)
		{
			mainCharacter->lockedAI->RecieveHit();
		}
	}
	
	UE_LOG(Log171General, Log, TEXT("Parry()"));
}

void StateMC_LockedOnMove::Dodge()
{
	State_MainCharacter::Dodge();
	RequestStateChange(TidesStateName::LockedOnDodging);
}

