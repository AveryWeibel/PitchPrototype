// Fill out your copyright notice in the Description page of Project Settings.


#include "State_MainCharacter.h"

#include "CustomDefines.h"
#include "MainCharacter.h"

DEFINE_LOG_CATEGORY(Log171MainCharState);

State_MainCharacter::State_MainCharacter(AMainCharacter* mainCharacterPtr)
{
	mainCharacter = mainCharacterPtr;
	check(mainCharacter);
	
	//Function pointer method (Abandoned)
	//StateAxisDelegates.Add(StateAction::MoveForward, &State_MainCharacter::MoveForward);
}

void State_MainCharacter::MoveCharacter(float DeltaTime, float MovementModifier, bool GroundSnap, float GravityAmount, bool UseStickMagnitudeForSpeed, FVector2D OverrideDirection) {

	//Remove physics forces
	mainCharacter->bodyCollider->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
	mainCharacter->bodyCollider->SetAllPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	
	//Sets HorizontalVector
	CalculateVelocityHorizontal(DeltaTime, MovementModifier, UseStickMagnitudeForSpeed, OverrideDirection);

	//Vertical must be checked after horizontal
	//Sets VerticalVector
	CalculateVerticalPosition(DeltaTime, GroundSnap);

	//Apply Gravity
	ApplyGravity(GravityAmount, DeltaTime);
	
	//Translate character
	*movementVector = FVector(HorizontalDirVector->X, HorizontalDirVector->Y, VerticalVector);//FMath::Lerp(*movementVector, FVector(HorizontalDirVector->X, HorizontalDirVector->Y, VerticalVector), 1.0f * DeltaTime);

	mainCharacter->AddActorWorldOffset(*movementVector, false);

	//Speed measurements
	const FVector DeltaVector = *HorizontalDirVector/DeltaTime;
	ActualSpeed = FVector(DeltaVector.X, DeltaVector.Y, 0).Size();

	//PositionLastFrame = mainCharacter->feetCollider->GetComponentLocation();

	UE_LOG(Log171MainCharState, Log, TEXT("Horizontal Movement Speed: %f\nHorizontal Vector: X: %f, Y: %f"), ActualSpeed, HorizontalDirVector->X, HorizontalDirVector->Y);
	if(VerticalVector > 0.0f)
	{
		//UE_LOG(Log171General, Log, TEXT("Vertical Vector: %f"), VerticalVector)
	}

	//Update external velocity fields
	mainCharacter->horizontalVelocity = FMath::Lerp(mainCharacter->horizontalVelocity, FVector(DeltaVector.X, DeltaVector.Y, 0), FMath::Clamp( HitWall ? 0.85f : 8.0f * DeltaTime, 0.0f, 1.0f));

	//UE_LOG(Log171MainCharState, Log, TEXT("Final PosTF: X:%f Y:%f Z:%f"), mainCharacter->bodyCollider->GetComponentLocation().X, mainCharacter->bodyCollider->GetComponentLocation().Y, mainCharacter->bodyCollider->GetComponentLocation().Z);
	//UE_LOG(Log171MainCharState, Log, TEXT("DeltaTime: %f"), DeltaTime);
	
	*HorizontalDirVector = FVector::ZeroVector;
	VerticalVector = 0;
	
	//mainCharacter->bodyCollider->SetWorldRotation(FRotator(0, 0, 0));
}

void State_MainCharacter::CalculateVerticalPosition(float DeltaTime, bool GroundSnap)
{
	FVector GroundTraceVerticalOffset = FVector(0, 0, mainCharacter->StepUpHeight);
	FCollisionShape GroundTraceShape = FCollisionShape::MakeSphere(mainCharacter->bodyCollider->GetScaledCapsuleRadius()/4);

	//Perform ground check
	const FVector GroundTraceEndLocation = mainCharacter->bodyCollider->GetComponentLocation() - GroundTraceVerticalOffset;
	if(
		mainCharacter->GetWorld()->SweepSingleByChannel(
			groundTraceResult,
			mainCharacter->bodyCollider->GetComponentLocation(),
			GroundTraceEndLocation,
			mainCharacter->bodyCollider->GetComponentRotation().Quaternion(),
			ECollisionChannel::ECC_WorldStatic,
			GroundTraceShape,
			groundTraceParams
		)
	)
	{
		//parentStateMachine->SendInput(StateAction::OverlapFeet);
		DrawDebugSphere(mainCharacter->GetWorld(), groundTraceResult.Location, GroundTraceShape.GetCapsuleRadius(), 20, FColor::Purple, false, 0.1f);
		IsGrounded = true;
		UE_LOG(Log171MainCharState, Log, TEXT("GroundTrace Hit: %s"), *groundTraceResult.Actor->GetName())
	}
	else
	{
		DrawDebugSphere(mainCharacter->GetWorld(), GroundTraceEndLocation, GroundTraceShape.GetCapsuleRadius(), 20, FColor::Yellow, false, 0.1f);
		IsGrounded = false;
	}
	UE_LOG(Log171MainCharState, Log, TEXT("IsGrounded: %s"), IsGrounded ? TEXT("True") : TEXT("False"));

	//Snap to ground if found
	if(GroundSnap && IsGrounded)
	{
		mainCharacter->bodyCollider->SetWorldLocation(groundTraceResult.Location + GroundTraceVerticalOffset);
		UE_LOG(Log171MainCharState, Log, TEXT("Snapped to: X:%f Y:%f Z:%f"), mainCharacter->bodyCollider->GetComponentLocation().X, mainCharacter->bodyCollider->GetComponentLocation().Y, mainCharacter->bodyCollider->GetComponentLocation().Z);
	}
}

void State_MainCharacter::CalculateVelocityHorizontal(float DeltaTime, float MovementModifier, bool UseStickMagnitudeForSpeed, FVector2D OverrideDirection)
{
	float stickLength = FMath::Sqrt((InputValues.X * InputValues.X) + (InputValues.Y * InputValues.Y));
	
	if (OverrideDirection != FVector2D::ZeroVector)
	{
		DirVector = OverrideDirection;
	}
	else
	{
		DirVector = (RightDirectionVector + ForwardDirectionVector);
	}
	
	if(InputValues.X != 0 || InputValues.Y != 0)
	{
		// UE_LOG(Log171MainCharState, Log, TEXT("Damping Value: %f"),
		// chestSweepResult.Normal.Z
		// );;
		DirVector.Normalize();
		//DirVector *= DeltaTime;
		*HorizontalDirVector = FVector(DirVector.X, DirVector.Y, 0);
		//HorizontalDirVector->Normalize();
		if(UseStickMagnitudeForSpeed)
		{
			*HorizontalDirVector *= FMath::Clamp(stickLength, 0.0f, 1.0f);
		}
		*HorizontalDirVector *= mainCharacter->accelerationForce * MovementModifier;
		*HorizontalDirVector *= DeltaTime;
	}

	//Spherecast forward check for slope
	// bool chestSweepHit = mainCharacter->GetWorld()->SweepSingleByChannel(
	// 	chestSweepResult,
	// 	mainCharacter->feetCollider->GetComponentLocation() + FVector(0, 0, mainCharacter->StepUpHeight),
	// 	(mainCharacter->feetCollider->GetComponentLocation() + FVector(0, 0, mainCharacter->StepUpHeight) + (FVector(DirVector.X, DirVector.Y, 0) * mainCharacter->feetCollider->GetScaledCapsuleRadius())),
	// 	mainCharacter->feetCollider->GetComponentRotation().Quaternion(),
	// 	ECC_WorldStatic,
	// 	FCollisionShape::MakeSphere(mainCharacter->feetCollider->GetScaledCapsuleRadius()),
	// 	groundTraceParams
	// );

	// HitWall = false;
	// if (chestSweepHit && slopeUpCheck)
	// {
	// 	//Debugging
	// 	DrawDebugSphere(mainCharacter->GetWorld(), chestSweepResult.Location, mainCharacter->feetCollider->GetScaledCapsuleRadius(), 20, FColor::Green, false, 0.1f);
	// 	UE_LOG(Log171MainCharState, Log, TEXT("Sphere hit obj: %s"), *chestSweepResult.Actor->GetName())
	//
	// 	//Reverse movement if moving into wall
	// 	*HorizontalDirVector *= 0.0f;
	// 	HitWall = true;
	// }
}

void State_MainCharacter::PerformGroundCheck()
{
	//Spherecast down, check for drop height

}

void State_MainCharacter::RotateCharacterModel(float DeltaTime, FVector FaceDirection, float turningRate)
{
	if(InputValues.Size() == 0)
	{
		return;
	}
	
	mainCharacter->Mesh->SetWorldRotation(
		FMath::Lerp
		(
			mainCharacter->Mesh->GetComponentRotation(),
			FRotator
			(
				mainCharacter->Mesh->GetComponentRotation().Pitch,
				FaceDirection.Rotation().Yaw,
				mainCharacter->Mesh->GetComponentRotation().Roll
			),
			FMath::Clamp
			(
				turningRate * DeltaTime,
				0.0f,
				1.0f
			)
		)
	);
}

void State_MainCharacter::ApplyGravity(float GravityAmount, float DeltaTime)
{
	VerticalVector += GravityAmount;// FMath::Clamp(GravityAmount * DeltaTime, -98.1f, 0.0f);
}

void State_MainCharacter::GetRightInput(float Value)
{
	FVector direction = mainCharacter->cameraBoom->GetRightVector();
	direction.Z = 0;
	direction *= (Value);
	RightDirectionVector = FVector2D(direction.X, direction.Y);
	InputValues.X = Value;
}

void State_MainCharacter::GetForwardInput(float Value)
{
	FVector direction = mainCharacter->cameraBoom->GetForwardVector();
	direction.Z = 0;
	direction *= (Value);
	ForwardDirectionVector = FVector2D(direction.X, direction.Y);
	InputValues.Y = Value;
}

void State_MainCharacter::AddCameraOrbitYaw(float Value)
{
	*cameraTurnVector += FRotator(
		0,
		  FMath::Clamp(Value * mainCharacter->cameraAccelerationForce, -mainCharacter->maxCameraVelocity, mainCharacter->maxCameraVelocity),
		0);
}

void State_MainCharacter::AddCameraOrbitPitch(float Value)
{
	*cameraTurnVector += FRotator(
		FMath::Clamp(-Value * mainCharacter->cameraAccelerationForce, -mainCharacter->maxCameraVelocity, mainCharacter->maxCameraVelocity),
		0,
		0);
}

bool State_MainCharacter::IsInCameraView(FVector obj)
{
	//2Dify obj
	obj.Z = 0;

	//2Dify CameraPos
	FVector cameraPos = mainCharacter->mainCamera->GetComponentLocation();
	cameraPos = FVector(cameraPos.X, cameraPos.Y, 0);

	//Get direction to obj from camera
	FVector dirToObj = obj - cameraPos;
	dirToObj.Normalize();
	//UE_LOG(Log171MainCharState, Log, TEXT("Camera-Obj Direction [%f, %f]"), dirToObj.X, dirToObj.Y);

	//2Dify camera forward vector
	FVector cameraForward = mainCharacter->mainCamera->GetForwardVector();
	cameraForward.Z = 0;
	cameraForward.Normalize();

	//Get 2D dot product for basic direction checks
	float dot = FVector::DotProduct(dirToObj, cameraForward);
	//UE_LOG(Log171MainCharState, Log, TEXT("Camera-Obj Dot Product [%f]"), dot);
	
	if(dot > cameraFrontThreshold) { return true; }
	return false;
}

void State_MainCharacter::MoveCameraLocked(float DeltaTime, FVector dirToTarget, float speedMod)
{
	
	//Position the camera
	//Lerp to proper camera boom length
	mainCharacter->cameraBoom->TargetArmLength = FMath::Lerp(mainCharacter->cameraBoom->TargetArmLength, mainCharacter->cameraLockedBoomLength, mainCharacter->cameraLerpAlpha * speedMod * DeltaTime);

	//Lerp cameraBoom to rotate between player and target
	cameraBoomRotationLerpTarget = (dirToTarget).Rotation();
	mainCharacter->cameraBoom->SetWorldRotation(FMath::Lerp(mainCharacter->cameraBoom->GetComponentRotation(), cameraBoomRotationLerpTarget, FMath::Clamp(mainCharacter->cameraLerpAlpha * 35 * speedMod * DeltaTime, DeltaTime, mainCharacter->cameraLerpAlpha)));	


	//Lerp to camera height
	//& Kick camera to the side for framing
	mainCharacter->cameraBoom->SetRelativeLocation(
		FVector (
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().X, mainCharacter->cameraLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().X, mainCharacter->cameraLerpAlpha * speedMod * DeltaTime),
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Y, mainCharacter->cameraLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().Y, mainCharacter->cameraLerpAlpha * speedMod * DeltaTime),
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Z, mainCharacter->cameraLockedHeight, mainCharacter->cameraLerpAlpha * speedMod * DeltaTime)
		)
	);

	//Lerp camera to face target
	cameraRotationLerpTarget = dirToTarget.Rotation();
	mainCharacter->mainCamera->SetWorldRotation(FMath::Lerp(mainCharacter->mainCamera->GetComponentRotation(), cameraRotationLerpTarget, mainCharacter->cameraLerpAlpha * speedMod * DeltaTime));
}

void State_MainCharacter::MoveCameraUnLocked(float DeltaTime, float speedMod)
{
	//Rotate camera to face in same direction as cameraBoom
	cameraRotationLerpTarget = mainCharacter->cameraBoom->GetComponentRotation();
	mainCharacter->mainCamera->SetWorldRotation(FMath::Lerp(mainCharacter->mainCamera->GetComponentRotation(), cameraRotationLerpTarget, mainCharacter->cameraLerpAlpha * DeltaTime));

	//Lerp camera boom length to correct length
	mainCharacter->cameraBoom->TargetArmLength = FMath::Lerp(mainCharacter->cameraBoom->TargetArmLength, mainCharacter->cameraUnLockedBoomLength, mainCharacter->cameraLerpAlpha * DeltaTime);

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
}

void State_MainCharacter::RagdollModel()
{
	mainCharacter->RagdollModel();
}

void State_MainCharacter::CallInteractBP()
{
	mainCharacter->InteractBP();
}

void State_MainCharacter::SendInput(StateAction Action)
{
	switch (Action) {
	case StateAction::Jump:
		Jump();
		break;
	case StateAction::LockOn:
		LockOn();
		break;
	case StateAction::ToggleSprint:
		ToggleSprint();
		break;
	case StateAction::DoAttack:
		DoAttack();
		break;
	case StateAction::Parry:
		Parry();
		break;
	case StateAction::Dodge:
		Dodge();
		break;
	case StateAction::TakeHit:
		TakeHit();
		break;
	case StateAction::Die:
		Die();
		break;
	case StateAction::Interact:
		Interact();
		break;
	case StateAction::AnimEnd:
		AnimEnd();
		break;
	case StateAction::AnimHitboxActive:
		AnimHitboxActive();
		break;
	case StateAction::AnimHitboxInactive:
		AnimHitboxInactive();
		break;
	case StateAction::EndOverlapAI:
		EndOverlapAI();
		break;
	case StateAction::EnterWater:
		EnterWater();
		break;
	case StateAction::ExitWater:
		ExitWater();
		break;
	default:
		break;
	}
}

void State_MainCharacter::SendInput(StateAction Action, float Value)
{
	switch (Action) {
	case StateAction::MoveForward:
		MoveForward(Value);
		break;
	case StateAction::MoveRight:
		MoveRight(Value);
		break;
	case StateAction::TurnRate:
		TurnRate(Value);
		break;
	case StateAction::LookUpRate:
		LookUpRate(Value);
		break;
	default:
		break;
	}

}

void State_MainCharacter::SendInput(StateAction Action, AActor& OtherActor)
{
	switch (Action) {
	case StateAction::OverlapFeet:
		BeginOverlapFeet(OtherActor);
		break;
	case StateAction::EndOverlapFeet:
		EndOverlapFeet(OtherActor);
		break;
	}
}

void State_MainCharacter::MoveForward(float)
{
}


void State_MainCharacter::MoveRight(float)
{
}

void State_MainCharacter::TurnRate(float)
{
}

void State_MainCharacter::LookUpRate(float)
{
}

void State_MainCharacter::AnimEnd()
{
	
}

void State_MainCharacter::AnimHitboxActive()
{
}

void State_MainCharacter::AnimHitboxInactive()
{
}

void State_MainCharacter::Jump()
{
}

void State_MainCharacter::LockOn()
{
}

void State_MainCharacter::ToggleSprint()
{
}

void State_MainCharacter::DoAttack()
{
}

void State_MainCharacter::Parry()
{
}

void State_MainCharacter::Dodge()
{
}

void State_MainCharacter::TakeHit()
{
}

void State_MainCharacter::Die()
{
}

void State_MainCharacter::Interact()
{
}

void State_MainCharacter::BeginOverlapFeet(AActor& OtherActor)
{
}

void State_MainCharacter::EndOverlapFeet(AActor& OtherActor)
{
}

void State_MainCharacter::StartOverlapAI()
{
}

void State_MainCharacter::EndOverlapAI()
{
}

void State_MainCharacter::EnterWater()
{
}

void State_MainCharacter::ExitWater()
{
}

State_MainCharacter::~State_MainCharacter()
{
}

void State_MainCharacter::RequestStateChange(TidesStateName StateName)
{
	State::RequestStateChange(StateName);
	mainCharacter->Animator->RecieveStateUpdate(StateName);
}

void State_MainCharacter::SweepForInteractables()
{
	for (auto AI : mainCharacter->InteractableList)
	{
		if(IsInCameraView(AI->GetActorLocation()))
		{
			if(focusedInteractable == nullptr)
			{
				focusedInteractable = AI;
				Cast<IInteractableInterface>(AI)->Execute_ReactToFocus(AI);
			}
			else if (AI == focusedInteractable)
			{
				Cast<IInteractableInterface>(focusedInteractable)->Execute_WhileFocused(focusedInteractable);
			}
			return;
		}
	}

	if(focusedInteractable != nullptr)
	{
		Cast<IInteractableInterface>(focusedInteractable)->Execute_ReactToUnFocus(focusedInteractable);
		focusedInteractable = nullptr;
	}
}