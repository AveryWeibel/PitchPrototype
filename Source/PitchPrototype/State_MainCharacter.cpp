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

//Apply inputs for this frame to movement vector and reset them to zero
void State_MainCharacter::ConsumeMoveInputs()
{
	moveFwd = moveRht = moveZ = 0;
}

void State_MainCharacter::ConsumeCameraInput(float DeltaTime)
{
	//cameraTurnVector->Add(-cameraInputY * DeltaTime, cameraInputX * DeltaTime, 0);
	
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
	mainCharacter->cameraBoom->TargetArmLength = FMath::Lerp(mainCharacter->cameraBoom->TargetArmLength, cameraBoomTargetLength, mainCharacter->cameraLerpAlpha * speedMod * DeltaTime);

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
	cameraRotationLerpTarget = (mainCharacter->lockedObject->GetActorLocation() - mainCharacter->mainCamera->GetComponentLocation()).Rotation();
	mainCharacter->mainCamera->SetWorldRotation(FMath::Lerp(mainCharacter->mainCamera->GetComponentRotation(), cameraRotationLerpTarget, mainCharacter->cameraLerpAlpha * speedMod * DeltaTime));
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
	case StateAction::BeginOverlapFeet:
		BeginOverlapFeet();
		break;
	case StateAction::EndOverlapFeet:
		EndOverlapFeet();
		break;
	case StateAction::LockOn:
		LockOn();
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

void State_MainCharacter::BeginOverlapFeet()
{
}

void State_MainCharacter::EndOverlapFeet()
{
}

void State_MainCharacter::StartOverlapAI()
{
}

void State_MainCharacter::EndOverlapAI()
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