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
	
	sprinting = false;
	
	UE_LOG(Log171NonCombatMove, Log, TEXT("Enter State NonCombatMove"));

	if(!mainCharacter->weapon->Sheathed || mainCharacter->Animator->GetSheatheAlpha() > 0.01f)
	{
		Sheathing = true;
	}
}

void StateMC_NonCombatMove::Execute(float DeltaTime)
{
	
	if(Sheathing)
	{
		UE_LOG(Log171NonCombatMove, Log, TEXT("SheatheAlpha: %f"), mainCharacter->Animator->GetSheatheAlpha());
		if(!mainCharacter->weapon->Sheathed)
		{
			mainCharacter->Animator->SetSheatheAlpha(mainCharacter->Animator->GetSheatheAlpha() + mainCharacter->WeaponSheatheSpeed * DeltaTime);
			if(mainCharacter->Animator->GetSheatheAlpha() >= 0.99f)
			{
				mainCharacter->weapon->Sheathed = true;
				mainCharacter->weapon->AttachToComponent(mainCharacter->Mesh, weaponAttachmentRules, FName("BackSocket"));
				UE_LOG(Log171NonCombatMove, Log, TEXT("Attach to back"));
			}
		}
		else
		{
			mainCharacter->Animator->SetSheatheAlpha(mainCharacter->Animator->GetSheatheAlpha() - mainCharacter->WeaponSheatheSpeed * DeltaTime);
			if(mainCharacter->Animator->GetSheatheAlpha() <= 0.01f)
			{
				mainCharacter->Animator->SetSheatheAlpha(0.0f);
				UE_LOG(Log171NonCombatMove, Log, TEXT("End sheathe animation"));
				Sheathing = false;
			}
		}
	}

	if(mainCharacter->currentPhysicsLinearVelocity.Z > .25)
	{
		//UE_LOG(Log171NonCombatMove, Log, TEXT("Moving Up by %f [%f]"), mainCharacter->currentPhysicsLinearVelocity.Z, UGameplayStatics::GetRealTimeSeconds(mainCharacter->GetWorld()));
	}

	//Position the camera
	MoveCameraUnLocked(DeltaTime);

	//Rotate model towards the movement vector
	RotateCharacterModel(DeltaTime, mainCharacter->horizontalVelocity, mainCharacter->modelTurningRate);

	if(InputValues.Size() < 0.875f)
	{
		sprinting = false;
	}
	
	//Move the character
	MoveCharacter(DeltaTime, (sprinting ? mainCharacter->SprintMultiplier : 1), true, mainCharacter->fallingGravityAmount, true);
	
	//Ensure collision does not rotate
	//mainCharacter->feetCollider->SetWorldRotation(FRotator(0, 0, 0));
	//*movementVector = FVector::ZeroVector;

	SweepForInteractables();
	
	if(!IsGrounded)
	{
		RequestStateChange(TidesStateName::NonCombatInAir);
	}
	
} //End Execute()

void StateMC_NonCombatMove::MoveForward(float Value)
{
	GetForwardInput(Value);
}

void StateMC_NonCombatMove::MoveRight(float Value)
{
	GetRightInput(Value);
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

void StateMC_NonCombatMove::ToggleSprint()
{
	State_MainCharacter::ToggleSprint();
	sprinting = !sprinting;
	UE_LOG(Log171NonCombatMove, Log, TEXT("Sprinting: %s"), sprinting ? TEXT("True") : TEXT("False"));
}

void StateMC_NonCombatMove::Die()
{
	State_MainCharacter::Die();
	RequestStateChange(TidesStateName::Dead);
}

void StateMC_NonCombatMove::BeginOverlapFeet(AActor& OtherActor)
{
	
}

void StateMC_NonCombatMove::EndOverlapFeet(AActor& OtherActor)
{
	// if (!OtherActor.Tags.Contains("Ocean"))
	// {
	// 	//UE_LOG(Log171NonCombatMove, Log, TEXT("End overlap feet"));
	// 	if (!IsGrounded)
	// 	{
	// 		RequestStateChange(TidesStateName::NonCombatInAir);
	// 	}
	// }
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

void StateMC_NonCombatMove::EnterWater()
{
	State_MainCharacter::EnterWater();
	RequestStateChange(TidesStateName::InWater);
}




