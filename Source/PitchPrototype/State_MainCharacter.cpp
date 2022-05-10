// Fill out your copyright notice in the Description page of Project Settings.


#include "State_MainCharacter.h"
#include "MainCharacter.h"

DEFINE_LOG_CATEGORY(Log171MainCharState);

State_MainCharacter::State_MainCharacter(AMainCharacter* mainCharacterPtr)
{
	mainCharacter = mainCharacterPtr;
	check(mainCharacter);

	//Function pointer method (Abandoned)
	//StateAxisDelegates.Add(StateAction::MoveForward, &State_MainCharacter::MoveForward);
}

void State_MainCharacter::MoveCharacter(float DeltaTime, float MovementModifier, bool slopeUpCheck, bool slopeDownCheck)
{
	//Spherecast down, check for drop height
	if(mainCharacter->GetWorld()->SweepSingleByChannel(groundTraceResult,
		mainCharacter->feetCollider->GetComponentLocation(),
		(mainCharacter->feetCollider->GetComponentLocation() - FVector(0, 0, 1000000)),
		mainCharacter->feetCollider->GetComponentRotation().Quaternion(),
		ECollisionChannel::ECC_WorldStatic,
		FCollisionShape::MakeSphere(mainCharacter->feetCollider->GetScaledCapsuleRadius()),
		groundTraceParams)
		&& slopeDownCheck)
	{
		//Calculate drop height this frame
		float StepDown = -FMath::Abs((mainCharacter->feetCollider->GetComponentLocation() - groundTraceResult.ImpactPoint + mainCharacter->feetCollider->GetScaledCapsuleRadius()).Z) * DeltaTime; //*10 to account for deltatime

		//Validate StepDown
		if (StepDown < 0 && StepDown >= -mainCharacter->StepDownHeight)
		{
			VerticalVector += StepDown;
			StepDownThisFrame = true;
		}
		else
		{
			StepDownThisFrame = false;
		}

		//Debugging
		if((movementVector->X != 0 || movementVector->Y != 0) || StepDown < -mainCharacter->StepDownHeight)
		{
			// UE_LOG(Log171MainCharState, Log, TEXT("StepDown: %f, %s"),
			// 	StepDown,
			// 	StepDownThisFrame ? TEXT("True") : TEXT("False")
			// );
		}
		
		//UE_LOG(Log171NonCombatMove, Log, TEXT("Normal Dot { %s }: %f"), *groundTraceResult.Actor->GetName(), FVector::DotProduct(groundTraceResult.Normal, FVector::ZAxisVector));
		//UE_LOG(Log171NonCombatMove, Log, TEXT("Normal Dot { %s }: %f"), *groundTraceResult.Actor->GetName(), movementVector->Z);
	}
	else
	{
		StepDownThisFrame = false;
	}

	//Spherecast forward check for slope
	bool chestSweepHit = mainCharacter->GetWorld()->SweepSingleByChannel(
		chestSweepResult,
		mainCharacter->bodyCollider->GetComponentLocation(),
		(mainCharacter->feetCollider->GetComponentLocation() + FVector(0, 0, mainCharacter->StepUpHeight) + (FVector(movementVector->X, movementVector->Y, 0) * 6 * DeltaTime)),
		mainCharacter->bodyCollider->GetComponentRotation().Quaternion(),
		ECC_WorldStatic,
		FCollisionShape::MakeSphere(mainCharacter->feetCollider->GetScaledCapsuleRadius()/2),
		groundTraceParams
	);
	
	if (chestSweepHit && slopeUpCheck)
	{
		DrawDebugSphere(mainCharacter->GetWorld(), chestSweepResult.Location, mainCharacter->feetCollider->GetScaledCapsuleRadius()/2, 20, FColor::Green, false, 0.1f);
		UE_LOG(Log171MainCharState, Log, TEXT("Sphere hit obj: %s"), *chestSweepResult.Actor->GetName())
	}

	if(StepDownThisFrame && slopeDownCheck)
	{
		DrawDebugSphere(mainCharacter->GetWorld(), groundTraceResult.Location, mainCharacter->feetCollider->GetScaledCapsuleRadius(), 20, FColor::Purple, false, 0.1f);
	}
	else
	{
		DrawDebugSphere(mainCharacter->GetWorld(), groundTraceResult.Location, mainCharacter->feetCollider->GetScaledCapsuleRadius(), 20, FColor::Yellow, false, 0.1f);
	}

	//Debugging
	float stickLength = FMath::Sqrt((InputValues.X * InputValues.X) + (InputValues.Y * InputValues.Y));
	if(InputValues.X != 0 || InputValues.Y != 0)
	{
		// UE_LOG(Log171MainCharState, Log, TEXT("Damping Value: %f"),
		// chestSweepResult.Normal.Z
		// );
		FVector2D DirVector = (RightDirectionVector + ForwardDirectionVector);
		DirVector.Normalize();
		//DirVector *= DeltaTime;
		*HorizontalDirVector = FVector(DirVector.X, DirVector.Y, 0);
		//HorizontalDirVector->Normalize();
		*HorizontalDirVector *= FMath::Clamp(stickLength, 0.0f, 1.0f);
		*HorizontalDirVector *= mainCharacter->accelerationForce * MovementModifier;
		*HorizontalDirVector *= DeltaTime;
	}

	//Translate character
	if(chestSweepHit && slopeUpCheck/*&& PrevStepDirVector.Z <= mainCharacter->StepUpHeight && stepHeightThisFrame <= mainCharacter->StepUpHeight*/)
	{
		*HorizontalDirVector *= 0.1f;
	}
	
	*movementVector = FVector(HorizontalDirVector->X, HorizontalDirVector->Y, VerticalVector);//FMath::Lerp(*movementVector, FVector(HorizontalDirVector->X, HorizontalDirVector->Y, VerticalVector), 1.0f * DeltaTime);

	mainCharacter->AddActorWorldOffset(*movementVector, false);

	//Speed measurements
	const FVector DeltaVector = *HorizontalDirVector/DeltaTime;
	ActualSpeed = FVector(DeltaVector.X, DeltaVector.Y, 0).Size();

	//PositionLastFrame = mainCharacter->feetCollider->GetComponentLocation();

	UE_LOG(Log171MainCharState, Log, TEXT("Horizontal Movement Speed: %f\nStickLen: %f\nHorizontal Vector: X: %f, Y: %f"), ActualSpeed, stickLength, HorizontalDirVector->X, HorizontalDirVector->Y);
	if(VerticalVector > 0.0f)
	UE_LOG(Log171General, Log, TEXT("Vertical Vector: %f"), VerticalVector)

	//Update external velocity fields
	mainCharacter->horizontalVelocity = FMath::Lerp(mainCharacter->horizontalVelocity, FVector(DeltaVector.X, DeltaVector.Y, 0), FMath::Clamp(10.0f * DeltaTime, 0.0f, 1.0f));

	*HorizontalDirVector = FVector::ZeroVector;
	VerticalVector = 0;
	
	mainCharacter->feetCollider->SetWorldRotation(FRotator(0, 0, 0));
}

void State_MainCharacter::RotateCharacterModel(float DeltaTime, FVector FaceDirection, float turningRate)
{
	if(FaceDirection.Size() == 0)
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
				DeltaTime,
				1.0f
			)
		)
	);
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
	case StateAction::BeginOverlapFeet:
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