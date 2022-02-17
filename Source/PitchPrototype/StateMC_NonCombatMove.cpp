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
	stateName = TidesStateName::NonCombatMove;
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
	//mainCharacter->Animator->SetLookAtTarget(mainCharacter->AIList->);


	//UE_LOG(Log171General, Log, TEXT("Fwd: %f, Rht: %f"), FMath::Abs(moveFwd), FMath::Abs(moveRht));
	
	ConsumeMoveInputs();
	ConsumeCameraInput(DeltaTime);

	if(mainCharacter->currentPhysicsLinearVelocity.Z > .25)
	{
		//UE_LOG(Log171NonCombatMove, Log, TEXT("Moving Up by %f [%f]"), mainCharacter->currentPhysicsLinearVelocity.Z, UGameplayStatics::GetRealTimeSeconds(mainCharacter->GetWorld()));
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
	//UE_LOG(Log171NonCombatMove, Log, TEXT("[RotateCameraRoll] Moving to %f from %f by %f"), cameraRotationLerpTarget.Roll, mainCharacter->mainCamera->GetComponentRotation().Roll, mainCharacter->cameraLerpAlpha * 3 * DeltaTime);
	//UE_LOG(Log171NonCombatMove, Log, TEXT("[RotateCameraPitch] Moving to %f from %f by %f"), cameraRotationLerpTarget.Pitch, mainCharacter->mainCamera->GetComponentRotation().Pitch, mainCharacter->cameraLerpAlpha * 3 * DeltaTime);
	//UE_LOG(Log171NonCombatMove, Log, TEXT("[RotateCameraYaw] Moving to %f from %f by %f"), cameraRotationLerpTarget.Yaw, mainCharacter->mainCamera->GetComponentRotation().Yaw, mainCharacter->cameraLerpAlpha * 3 * DeltaTime);
	mainCharacter->mainCamera->SetWorldRotation(FMath::Lerp(mainCharacter->mainCamera->GetComponentRotation(), cameraRotationLerpTarget, mainCharacter->cameraLerpAlpha * DeltaTime));

	//Lerp camera boom length to correct length
	//UE_LOG(Log171NonCombatMove, Log, TEXT("[CameraBoomLength] Moving to %f from %f by %f"), cameraBoomTargetLength, mainCharacter->cameraBoom->TargetArmLength, mainCharacter->cameraLerpAlpha * DeltaTime);
	mainCharacter->cameraBoom->TargetArmLength = FMath::Lerp(mainCharacter->cameraBoom->TargetArmLength, cameraBoomTargetLength, mainCharacter->cameraLerpAlpha * DeltaTime);

	//Rotate cameraBoom to face turnvector
	cameraBoomRotationLerpTarget = *cameraTurnVector;
	//UE_LOG(Log171NonCombatMove, Log, TEXT("%f"), FMath::Clamp(mainCharacter->cameraLerpAlpha * 35 * DeltaTime, DeltaTime, mainCharacter->cameraLerpAlpha));
	mainCharacter->cameraBoom->SetWorldRotation(FMath::Lerp(mainCharacter->cameraBoom->GetRelativeRotation(), cameraBoomRotationLerpTarget,  FMath::Clamp(mainCharacter->cameraLerpAlpha * 35 * DeltaTime, DeltaTime, mainCharacter->cameraLerpAlpha)));	
	
	//	UE_LOG(Log171NonCombatMove, Log, TEXT("[MoveCameraBoomX] Moving to %f from %f by %f"), mainCharacter->cameraUnLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().X, mainCharacter->cameraBoom->GetRelativeLocation().X, mainCharacter->cameraLerpAlpha * DeltaTime);
	//	UE_LOG(Log171NonCombatMove, Log, TEXT("[MoveCameraBoomY] Moving to %f from %f by %f"), mainCharacter->cameraUnLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().Y, mainCharacter->cameraBoom->GetRelativeLocation().Y, mainCharacter->cameraLerpAlpha * DeltaTime);
	//	UE_LOG(Log171NonCombatMove, Log, TEXT("[MoveCameraBoomZ] Moving to %f from %f by %f"), mainCharacter->cameraUnLockedHeight, mainCharacter->cameraBoom->GetRelativeLocation().Z, mainCharacter->cameraLerpAlpha * DeltaTime);
	mainCharacter->cameraBoom->SetRelativeLocation(
		FVector (
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().X, mainCharacter->cameraUnLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().X, mainCharacter->cameraLerpAlpha * DeltaTime),
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Y, mainCharacter->cameraUnLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().Y, mainCharacter->cameraLerpAlpha * DeltaTime),
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Z, mainCharacter->cameraUnLockedHeight, mainCharacter->cameraLerpAlpha * DeltaTime)
		)
	);

	//Rotate model towards the movement vector
	if (movementVector->Size() > 0)
	{
		mainCharacter->Mesh->SetWorldRotation(FMath::Lerp(mainCharacter->Mesh->GetRelativeRotation(),  movementVector->Rotation(), FMath::Clamp( 4 * DeltaTime, DeltaTime, 4.0f)));
	}

		//float turnDelta = 
		
		//UE_LOG(Log171General, Log, TEXT("MovementDirection X[%f], Y[%f], Z[%f]"), movementVector->X, movementVector->Y, movementVector->Z);


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
	cameraInputX += FMath::Clamp<float>(Value, -10.0, 10.0) * mainCharacter->cameraAccelerationForce;
}

void StateMC_NonCombatMove::LookUpRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnY [%f]"), Value);
	cameraInputY += FMath::Clamp<float>(Value, -10.0, 10.0) * mainCharacter->cameraAccelerationForce;
}

void StateMC_NonCombatMove::Jump()
{
	RequestStateChange(TidesStateName::NonCombatJump);
}

void StateMC_NonCombatMove::LockOn()
{
	for (auto AI : mainCharacter->AIList)
	{
		if(IsInCameraView(AI->GetActorLocation()))
		{
			mainCharacter->lockedAI = AI;
			mainCharacter->lockedAI->PlayerLock();
			RequestStateChange(TidesStateName::LockedOnMove);
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


