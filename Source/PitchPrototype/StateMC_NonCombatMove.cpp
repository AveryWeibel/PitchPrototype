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
	//Set Ground Trace Params
	if(mainCharacter)
	{
		groundTraceParams.AddIgnoredActor(mainCharacter);
		//GroundTraceResponseParams.DefaultResponseParam.
	}
	
	UE_LOG(LogTemp, Log, TEXT("Enter State NonCombatMove"));
	cameraBoomTargetLength = mainCharacter->cameraUnLockedBoomLength;
	//*cameraTurnVector = mainCharacter->cameraBoom->GetRelativeRotation();
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
		//mainCharacter->feetCollider->AddForce(*movementVector);
		//movementVector->Z = -FMath::Abs(movementVector->X + movementVector->Y)/8;
		if(mainCharacter->GetWorld()->SweepSingleByChannel(groundTraceResult,
			mainCharacter->feetCollider->GetComponentLocation(),
			(mainCharacter->feetCollider->GetComponentLocation() - FVector(0, 0, 300)),
			mainCharacter->feetCollider->GetComponentRotation().Quaternion(),
			ECollisionChannel::ECC_WorldStatic,
			FCollisionShape::MakeSphere(mainCharacter->feetCollider->GetScaledCapsuleRadius()),
			groundTraceParams))
		{
			movementVector->Z = -(mainCharacter->feetCollider->GetComponentLocation() - (groundTraceResult.ImpactPoint + mainCharacter->feetCollider->GetScaledCapsuleRadius())).Z * 10; //*10 to account for deltatime
			//UE_LOG(Log171NonCombatMove, Log, TEXT("Normal Dot { %s }: %f"), *groundTraceResult.Actor->GetName(), FVector::DotProduct(groundTraceResult.Normal, FVector::ZAxisVector));
			//UE_LOG(Log171NonCombatMove, Log, TEXT("Normal Dot { %s }: %f"), *groundTraceResult.Actor->GetName(), movementVector->Z);
		}
		
		mainCharacter->AddActorWorldOffset(*movementVector *= DeltaTime);
		mainCharacter->horizontalVelocity = *movementVector;
	}

	//Position the camera
	//Rotate camera to face in same direction as cameraBoom
	cameraRotationLerpTarget = mainCharacter->cameraBoom->GetComponentRotation();
	mainCharacter->mainCamera->SetWorldRotation(FMath::Lerp(mainCharacter->mainCamera->GetComponentRotation(), cameraRotationLerpTarget, mainCharacter->cameraLerpAlpha * DeltaTime));

	//Lerp camera boom length to correct length
	mainCharacter->cameraBoom->TargetArmLength = FMath::Lerp(mainCharacter->cameraBoom->TargetArmLength, cameraBoomTargetLength, mainCharacter->cameraLerpAlpha * DeltaTime);

	//Rotate cameraBoom to face turnvector
	cameraBoomRotationLerpTarget = mainCharacter->cameraBoom->GetRelativeRotation() + *cameraTurnVector;
	cameraRotationLerpTarget.Roll = 0;
	cameraBoomRotationLerpTarget.Pitch = FMath::Clamp(cameraBoomRotationLerpTarget.Pitch, -60.0f, 60.0f);
	//UE_LOG(Log171MainCharState, Log, TEXT("cameraTurnVector: Pitch: %f, Yaw: %f, Roll: %f"), cameraTurnVector->Pitch, cameraTurnVector->Yaw, cameraTurnVector->Roll);
	
	mainCharacter->cameraBoom->SetRelativeRotation(FMath::Lerp(mainCharacter->cameraBoom->GetRelativeRotation(), cameraBoomRotationLerpTarget,  FMath::Clamp(mainCharacter->cameraLerpAlpha * DeltaTime, DeltaTime, mainCharacter->cameraLerpAlpha)));	
	
	mainCharacter->cameraBoom->SetRelativeLocation(
		FVector (
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().X, mainCharacter->cameraUnLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().X, mainCharacter->cameraLerpAlpha * DeltaTime),
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Y, mainCharacter->cameraUnLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().Y, mainCharacter->cameraLerpAlpha * DeltaTime),
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Z, mainCharacter->cameraUnLockedHeight, mainCharacter->cameraLerpAlpha * DeltaTime)
		)
	);

	*cameraTurnVector = FRotator::ZeroRotator;

	//Rotate model towards the movement vector
	if (movementVector->Size() > 0)
	{
		mainCharacter->Mesh->SetWorldRotation(FMath::Lerp(mainCharacter->Mesh->GetComponentRotation(),  movementVector->ToOrientationRotator(), FMath::Clamp( mainCharacter->modelTurningRate * DeltaTime, DeltaTime, mainCharacter->modelTurningRate)));
	}

		//float turnDelta = 
		
		//UE_LOG(Log171General, Log, TEXT("MovementDirection X[%f], Y[%f], Z[%f]"), movementVector->X, movementVector->Y, movementVector->Z);


	//Ensure collision does not rotate
	//mainCharacter->feetCollider->SetWorldRotation(FRotator(0, 0, 0));
	*movementVector = FVector::ZeroVector;
	mainCharacter->feetCollider->SetPhysicsLinearVelocity(FVector(0 ,0, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Z));

	SweepForInteractables();
} //End Execute()

void StateMC_NonCombatMove::MoveForward(float Value)
{
	moveFwd = Value;
	//if(Value != 0)
		//UE_LOG(Log171NonCombatMove, Log, TEXT("CharacterVelocity[X: %f, Y: %f, Z: %f]"), mainCharacter->feetCollider->GetPhysicsLinearVelocity().X, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Y, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Z);
	

	FVector direction = mainCharacter->cameraBoom->GetForwardVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce);
	*movementVector += FVector(direction.X, direction.Y, moveZ);
	//moveX = Value * mainCharacter->mainCamera->GetForwardVector().X * mainCharacter->accelerationForce;
}

void StateMC_NonCombatMove::MoveRight(float Value)
{
	//if (Value != 0)
		//UE_LOG(Log171NonCombatMove, Log, TEXT("CharacterVelocity[X: %f, Y: %f, Z: %f]"), mainCharacter->feetCollider->GetPhysicsLinearVelocity().X, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Y, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Z);

	//moveY = Value * mainCharacter->accelerationForce;
	FVector direction = mainCharacter->cameraBoom->GetRightVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce);
	*movementVector += FVector(direction.X, direction.Y, moveZ);
}

void StateMC_NonCombatMove::TurnRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnX [%f]"), Value);
	AddCameraOrbitYaw(Value);
}

void StateMC_NonCombatMove::LookUpRate(float Value)
{
	//UE_LOG(Log171NonCombatMove, Log, TEXT("CameraTurnY [%f]"), Value);
	AddCameraOrbitPitch(Value);
}

void StateMC_NonCombatMove::Jump()
{
	RequestStateChange(TidesStateName::NonCombatJump);
}

void StateMC_NonCombatMove::LockOn()
{
	if(focusedInteractable)
	{
		mainCharacter->lockedObject = focusedInteractable;
		Cast<IInteractableInterface>(focusedInteractable)->Execute_PlayerLock(mainCharacter->lockedObject);
		RequestStateChange(TidesStateName::LockedOnMove);
		UE_LOG(Log171NonCombatMove, Log, TEXT("Locked onto [%s]"), *mainCharacter->lockedObject->GetName());
	}
}

void StateMC_NonCombatMove::Die()
{
	State_MainCharacter::Die();
	RequestStateChange(TidesStateName::Dead);
}

void StateMC_NonCombatMove::BeginOverlapFeet()
{
	
}

void StateMC_NonCombatMove::EndOverlapFeet()
{
	//RequestStateChange(StateName::NonCombatInAir);
}

void StateMC_NonCombatMove::StartOverlapAI()
{
	State_MainCharacter::StartOverlapAI();
}

void StateMC_NonCombatMove::EndOverlapAI()
{
	State_MainCharacter::EndOverlapAI();
}

void StateMC_NonCombatMove::Interact()
{
	UE_LOG(Log171General, Log, TEXT("Call Interact()"))
	if(focusedInteractable)
	{
		auto interactable = Cast<IInteractableInterface>(focusedInteractable);
		
		interactable->Execute_PlayerInteract(focusedInteractable);
		if(interactable->Execute_InteractToLockOn(focusedInteractable))
		{
			StateMC_NonCombatMove::LockOn();	
		}

		//Call BP implementation
		CallInteractBP();
	}
}




