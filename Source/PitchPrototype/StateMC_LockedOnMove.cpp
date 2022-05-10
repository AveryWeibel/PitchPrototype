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
	//Set Ground Trace Params
	if(mainCharacter)
	{
		groundTraceParams.AddIgnoredActor(mainCharacter);
		//GroundTraceResponseParams.DefaultResponseParam.
	}
}

void StateMC_LockedOnMove::Execute(float DeltaTime)
{
	
	if(IsValid(mainCharacter->lockedObject))
	{
		//Update animation variables
		mainCharacter->Animator->SetLookAtTarget(mainCharacter->lockedObject->GetActorLocation());

		mainCharacter->Animator->SetControlDirection( FMath::Lerp( mainCharacter->Animator->GetControlDirection(), *HorizontalDirVector, 0.2f) );

		if(mainCharacter->Animator->GetParryAlpha() >= .95)
		{
			ParryLerpTarget = 0;
		}
		
		mainCharacter->Animator->SetParryAlpha(FMath::Lerp(mainCharacter->Animator->GetParryAlpha(), ParryLerpTarget, 10 * DeltaTime));

		//Move the character
		MoveCharacter(DeltaTime, mainCharacter->lockedMovementMultiplier, true, true);
		
		//Move the camera
		if (IsValid(mainCharacter->lockedObject))
		{
			dirToTarget = mainCharacter->lockedObject->GetActorLocation() - mainCharacter->GetActorLocation();
		}
		else
		{
			UE_LOG(Log171LockedOnMove, Warning, TEXT("locked object is invalid (This may be okay if the game didn't crash :D)"));
		}
	}
	else
	{
		UE_LOG(Log171LockedOnMove, Warning, TEXT("locked object is invalid (This may be okay if the game didn't crash :D)"));
	}
	
	//2D so the camera doesn't tilt with distance
	dirToTarget.Z = 0;
	MoveCameraLocked(DeltaTime, dirToTarget);

	//Rotate model towards the locked target
	RotateCharacterModel(DeltaTime, dirToTarget, mainCharacter->modelTurningRate);

	//Ensure collision does not rotate
	mainCharacter->feetCollider->SetWorldRotation(FRotator(0, 0, 0));

	SweepForInteractables();
}

void StateMC_LockedOnMove::MoveForward(float Value)
{
	GetForwardInput(Value);
}

void StateMC_LockedOnMove::MoveRight(float Value)
{
	GetRightInput(Value);
}

void StateMC_LockedOnMove::LockOn()
{
	UE_LOG(Log171LockedOnMove, Log, TEXT("Locked off of [%s]"), *mainCharacter->lockedObject->GetName());
	Cast<IInteractableInterface>(mainCharacter->lockedObject)->Execute_PlayerUnLock(mainCharacter->lockedObject);
	//*cameraTurnVector = mainCharacter->cameraBoom->GetComponentRotation();
	mainCharacter->lockedObject = nullptr;
	
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

void StateMC_LockedOnMove::Die()
{
	State_MainCharacter::Die();
	RequestStateChange(TidesStateName::Dead);
}

void StateMC_LockedOnMove::Parry()
{
	State_MainCharacter::Parry();
	
	if(mainCharacter->Animator->GetParryAlpha() <= .05f) {

		ABaseAICharacter* AI = Cast<ABaseAICharacter>(mainCharacter->lockedObject);
		
		if(AI)
		{
			if(AI->Weapon)
			{
				mainCharacter->Animator->SetParryIKTarget(AI->Weapon->GetActorLocation());
			}
			else
			{
				mainCharacter->Animator->SetParryIKTarget(mainCharacter->lockedObject->GetActorLocation());
			}
		
			ParryLerpTarget = 1;
			if(AI->Animator->GetParryable() && mainCharacter->GetDistanceTo(mainCharacter->lockedObject) < mainCharacter->parryDistance)
			{
				AI->RecieveParry();
			}
		}
	}
	
	UE_LOG(Log171General, Log, TEXT("Parry()"));
}

void StateMC_LockedOnMove::Dodge()
{
	State_MainCharacter::Dodge();
	RequestStateChange(TidesStateName::LockedOnDodging);
}

void StateMC_LockedOnMove::Interact()
{
	UE_LOG(Log171General, Log, TEXT("Call Interact()"))
	if(focusedInteractable)
	{
		auto interactable = Cast<IInteractableInterface>(focusedInteractable);
	
		interactable->Execute_PlayerInteract(focusedInteractable);

		//Call BP implementation
		CallInteractBP();
	}
}

void StateMC_LockedOnMove::EndOverlapAI()
{
	return;
	
	if (!mainCharacter->InteractableList.Contains(mainCharacter->lockedObject)) {
		mainCharacter->lockedObject = nullptr;

		auto interactable = Cast<IInteractableInterface>(focusedInteractable);
		interactable->Execute_PlayerUnLock(focusedInteractable);

		SweepForInteractables();
		RequestStateChange(TidesStateName::NonCombatMove);
	}

	UE_LOG(Log171General, Log, TEXT("Endoverlap AI"));
}

