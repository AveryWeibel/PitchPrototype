// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMC_NonCombatMove.h"
#include "MainCharacter.h"
#include "GameFramework/GameState.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(Log171NonCombatMove);

// Call parent Ctor
StateMC_NonCombatMove::StateMC_NonCombatMove(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	stateName = StateName::NonCombatMove;
}

StateMC_NonCombatMove::~StateMC_NonCombatMove()
{
}

void StateMC_NonCombatMove::Start()
{
	UE_LOG(LogTemp, Log, TEXT("Enter State NonCombatMove"));
	cameraBoomTargetLength = mainCharacter->cameraUnLockedBoomLength;
	*cameraTurnVector = mainCharacter->cameraBoom->GetRelativeRotation();
}

void StateMC_NonCombatMove::Execute(float DeltaTime)
{
	
	//Apply skeletal forces
	float tiltAmount = mainCharacter->Animator->GetTiltAmount();
	mainCharacter->Animator->SetTiltAmount(FMath::Lerp(tiltAmount, FMath::Abs(moveFwd) + FMath::Abs(moveRht), .01f));
	//mainCharacter->Animator->SetLookAtTarget(mainCharacter->AIList->);


	//UE_LOG(Log171General, Log, TEXT("Fwd: %f, Rht: %f"), FMath::Abs(moveFwd), FMath::Abs(moveRht));
	
	ConsumeMoveInputs();
	ConsumeCameraInput();

	if(mainCharacter->currentPhysicsLinearVelocity.Z > .25)
	{
		UE_LOG(Log171NonCombatMove, Log, TEXT("Moving Up by %f [%f]"), mainCharacter->currentPhysicsLinearVelocity.Z, UGameplayStatics::GetRealTimeSeconds(mainCharacter->GetWorld()));
	}

	//Move the character
	if (mainCharacter->currentPhysicsLinearVelocity.Size() <= mainCharacter->maximumHorizontalVelocity) {
		//FVector forceDirection(, , 0);
		mainCharacter->feetCollider->AddForce(*movementVector);
		//mainCharacter->AddActorWorldOffset(*movementVector / 500000);
	}

	//Position the camera
	//Rotate camera to face in same direction as cameraBoom
	cameraRotationLerpTarget = mainCharacter->cameraBoom->GetComponentRotation();
	if(mainCharacter->mainCamera->GetComponentRotation() != cameraRotationLerpTarget)
	{
		mainCharacter->mainCamera->SetWorldRotation(FMath::Lerp(mainCharacter->mainCamera->GetComponentRotation(), cameraRotationLerpTarget, mainCharacter->cameraLerpAlpha * 3));
	}

	//Lerp camera boom length to correct length
	if(mainCharacter->cameraBoom->TargetArmLength != cameraBoomTargetLength)
	{
		mainCharacter->cameraBoom->TargetArmLength = FMath::Lerp(mainCharacter->cameraBoom->TargetArmLength, cameraBoomTargetLength, mainCharacter->cameraLerpAlpha);
	}

	//Rotate cameraBoom to face turnvector
	cameraBoomRotationLerpTarget = *cameraTurnVector;
	if(mainCharacter->cameraBoom->GetRelativeRotation() != cameraBoomRotationLerpTarget)
	{
		mainCharacter->cameraBoom->SetWorldRotation(FMath::Lerp(mainCharacter->cameraBoom->GetRelativeRotation(), cameraBoomRotationLerpTarget, mainCharacter->cameraLerpAlpha * 50));	
	}

	if(mainCharacter->cameraBoom->GetRelativeLocation().Z != mainCharacter->cameraUnLockedHeight)
	{
		mainCharacter->cameraBoom->SetRelativeLocation(
			FVector (
				FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().X, mainCharacter->cameraUnLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().X, mainCharacter->cameraLerpAlpha),
				FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Y, mainCharacter->cameraUnLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().Y, mainCharacter->cameraLerpAlpha),
				FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Z, mainCharacter->cameraUnLockedHeight, mainCharacter->cameraLerpAlpha)
			)
		);
	}

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

void StateMC_NonCombatMove::MoveForward(float Value)
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

void StateMC_NonCombatMove::MoveRight(float Value)
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

void StateMC_NonCombatMove::TurnRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnX [%f]"), Value);
	cameraInputX += Value;
}

void StateMC_NonCombatMove::LookUpRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnY [%f]"), Value);
	cameraInputY += Value;
}

void StateMC_NonCombatMove::Jump()
{
	RequestStateChange(StateName::NonCombatJump);
}

void StateMC_NonCombatMove::LockOn()
{
	for (auto AI : mainCharacter->AIList)
	{
		if(IsInCameraView(AI->GetActorLocation()))
		{
			mainCharacter->lockedAI = AI;
			mainCharacter->lockedAI->PlayerLock();
			RequestStateChange(StateName::LockedOnMove);
			UE_LOG(Log171NonCombatMove, Log, TEXT("Locked onto [%s]"), *AI->GetName());
		}
	}
}

void StateMC_NonCombatMove::BeginOverlapFeet()
{
	
}

void StateMC_NonCombatMove::EndOverlapFeet()
{
	//RequestStateChange(StateName::NonCombatInAir);
}


