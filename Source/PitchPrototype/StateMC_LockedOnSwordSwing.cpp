// Fill out your copyright notice in the Description page of Project Settings.

//SETTINGS IN VISUAL STUDIO 2022
//Tools>Options>Text Editor>{Language}>Code Style>Formatting>"Choose When I paste, Indent, but do not format"

#include "StateMC_LockedOnSwordSwing.h"
#include "MainCharacter.h"
#include "CustomDefines.h"
#include "Curves/CurveVector.h"

DEFINE_LOG_CATEGORY(Log171Attack);

StateMC_LockedOnSwordSwing::StateMC_LockedOnSwordSwing(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	//Add new entry to StateName in State.h
	stateName = TidesStateName::SwordAttack;
}

StateMC_LockedOnSwordSwing::~StateMC_LockedOnSwordSwing()
{

}

void StateMC_LockedOnSwordSwing::Start()
{
	UE_LOG(LogTemp, Log, TEXT("Enter State StateMC_LockedOnSwordSwing"));
	if(mainCharacter)
	{
		groundTraceParams.AddIgnoredActor(mainCharacter);
		//GroundTraceResponseParams.DefaultResponseParam.
	}

	mainCharacter->Animator->StartAttackMontage();
}

void StateMC_LockedOnSwordSwing::Execute(float DeltaTime)
{
	//UE_LOG(LogTemp, Log, TEXT("Execute State StateMC_LockedOnSwordSwing"));
	//Setup moveVector

	//Check if we hit anything
	auto hitAI = Cast<ABaseAICharacter>(mainCharacter->weapon->overlappedPawn);
	if(!hitThisAttack && hitboxActive && hitAI)
	{
		if (Cast<ABaseAIController>(hitAI->GetController())->GetState() == TidesStateName::AI_CombatDialogue || Cast<ABaseAIController>(hitAI->GetController())->GetState() == TidesStateName::AI_RecieveHit) {
			RequestStateChange(TidesStateName::LockedOnTakeHit);
			hitThisAttack = true;
			hitAI->Animator->ParrySound();
		} else if (hitAI->canDodge && Cast<ABaseAIController>(hitAI->GetController())->GetState() == TidesStateName::AI_CombatStrafe) {
			hitAI->Dodge();
			hitThisAttack = true;
		} else {
			hitThisAttack = true;
			hitAI->RecieveHit(10);
		}
	}
	
	FVector dirToTarget = mainCharacter->lockedObject->GetActorLocation() - mainCharacter->GetActorLocation();
	dirToTarget.Z = 0;
	MoveCameraLocked(DeltaTime, dirToTarget);

	//Calculate movement this frame for attack
	FVector2D MovementDeltaThisFrame = FVector2D(mainCharacter->AttackVectorCurve->GetVectorValue(mainCharacter->Animator->GetMontageTime()) - MovementValueLastFrame);
	FVector2D ForwardComponent = FVector2D(dirToTarget * MovementDeltaThisFrame.X);
	FVector2D RightComponent = FVector2D(ForwardComponent.Y, -ForwardComponent.X) * MovementDeltaThisFrame.Y;
	
	FVector2D DirCorrectedDelta = ForwardComponent + RightComponent; // + FVector2D(dirToTarget.RightVector * MovementDeltaThisFrame.Y);
	
	UE_LOG(Log171Attack, Log, TEXT("MovementDelta: X: %f, Y: %f\nMontageTime: %f"), MovementDeltaThisFrame.X, MovementDeltaThisFrame.Y, mainCharacter->Animator->GetMontageTime());
	if(mainCharacter->Animator->GetMontageTime() > 0)
	{
		MoveCharacter(DeltaTime, 1.0f, true, mainCharacter->fallingGravityAmount, false, DirCorrectedDelta);
	}
	
	RotateCharacterModel(DeltaTime, dirToTarget, mainCharacter->attackTrackingIntensity, false);


	MovementValueLastFrame = mainCharacter->AttackVectorCurve->GetVectorValue(mainCharacter->Animator->GetMontageTime());
}

void StateMC_LockedOnSwordSwing::AnimEnd()
{
	State_MainCharacter::AnimEnd();
	hitThisAttack = false;

	ABaseAICharacter* AI = Cast<ABaseAICharacter>(mainCharacter->lockedObject);
	if(AI && AI->GetIsDead())
	{
		RequestStateChange(TidesStateName::NonCombatMove);	
	}
	else
	{
		RequestStateChange(TidesStateName::LockedOnMove);
	}
}

void StateMC_LockedOnSwordSwing::AnimHitboxActive()
{
	State_MainCharacter::AnimHitboxActive();
	hitboxActive = true;
	
}

void StateMC_LockedOnSwordSwing::AnimHitboxInactive()
{
	State_MainCharacter::AnimHitboxInactive();
	hitboxActive = false;
}

