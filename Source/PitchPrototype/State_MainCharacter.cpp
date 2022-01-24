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

void State_MainCharacter::ConsumeCameraInput()
{
	cameraTurnVector->Add(-cameraInputY, cameraInputX, 0);
	cameraTurnVector->Pitch = FMath::Clamp(cameraTurnVector->Pitch, -40.0f, 40.0f);
	cameraInputX = cameraInputY = 0;
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
	UE_LOG(Log171MainCharState, Log, TEXT("Camera-Obj Direction [%f, %f]"), dirToObj.X, dirToObj.Y);

	//2Dify camera forward vector
	FVector cameraForward = mainCharacter->mainCamera->GetForwardVector();
	cameraForward.Z = 0;
	cameraForward.Normalize();

	//Get 2D dot product for basic direction checks
	float dot = FVector::DotProduct(dirToObj, cameraForward);
	UE_LOG(Log171MainCharState, Log, TEXT("Camera-Obj Dot Product [%f]"), dot);
	
	if(dot > cameraFrontThreshold) { return true; }
	return false;
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

void State_MainCharacter::Jump()
{
}

void State_MainCharacter::LockOn()
{
}

void State_MainCharacter::BeginOverlapFeet()
{
}

void State_MainCharacter::EndOverlapFeet()
{
}

State_MainCharacter::~State_MainCharacter()
{
}

