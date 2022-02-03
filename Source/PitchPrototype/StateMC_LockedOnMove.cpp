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
	float tiltAmount = mainCharacter->Animator->GetTiltAmount();
	mainCharacter->Animator->SetTiltAmount(FMath::Lerp(tiltAmount, FMath::Abs(moveFwd) + FMath::Abs(moveRht), .01f));
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

	//Position the camera
	//Lerp to proper camera boom length
	if(mainCharacter->cameraBoom->TargetArmLength != cameraBoomTargetLength)
	{
		mainCharacter->cameraBoom->TargetArmLength = FMath::Lerp(mainCharacter->cameraBoom->TargetArmLength, cameraBoomTargetLength, mainCharacter->cameraLerpAlpha * DeltaTime);
	}

	//Lerp cameraBoom to rotate between player and target
	//2D so the camera doesn't tilt with distance
	FVector dirToTarget = mainCharacter->lockedAI->GetActorLocation() - mainCharacter->GetActorLocation();
	dirToTarget.Z = 0;
	cameraBoomRotationLerpTarget = (dirToTarget).Rotation();
	if(mainCharacter->cameraBoom->GetComponentRotation() != cameraBoomRotationLerpTarget)
	{
		mainCharacter->cameraBoom->SetWorldRotation(FMath::Lerp(mainCharacter->cameraBoom->GetComponentRotation(), cameraBoomRotationLerpTarget, mainCharacter->cameraLerpAlpha * 50 * DeltaTime));	
	}

	//Lerp to camera height
	//& Kick camera to the side for framing
	if(mainCharacter->cameraBoom->GetRelativeLocation().Z != mainCharacter->cameraLockedHeight)
	{
		mainCharacter->cameraBoom->SetRelativeLocation(
			FVector (
				FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().X, mainCharacter->cameraLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().X, mainCharacter->cameraLerpAlpha * DeltaTime),
				FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Y, mainCharacter->cameraLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().Y, mainCharacter->cameraLerpAlpha * DeltaTime),
				FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Z, mainCharacter->cameraLockedHeight, mainCharacter->cameraLerpAlpha * DeltaTime)
			)
		);
	}

	//Lerp camera to face target
	cameraRotationLerpTarget = (mainCharacter->lockedAI->GetActorLocation() - mainCharacter->mainCamera->GetComponentLocation()).Rotation();
	mainCharacter->mainCamera->SetWorldRotation(FMath::Lerp(mainCharacter->mainCamera->GetComponentRotation(), cameraRotationLerpTarget, mainCharacter->cameraLerpAlpha * DeltaTime));

	//Rotate model towards the movement vector
	if (movementVector->Size() > 0) {
		mainCharacter->Mesh->SetWorldRotation(FMath::Lerp(mainCharacter->Mesh->GetRelativeRotation(),  dirToTarget.Rotation(), 4 * DeltaTime));

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
	RequestStateChange(TidesStateName::SwordAttack);
}
