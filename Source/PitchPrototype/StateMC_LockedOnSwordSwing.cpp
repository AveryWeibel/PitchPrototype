// Fill out your copyright notice in the Description page of Project Settings.

//SETTINGS IN VISUAL STUDIO 2022
//Tools>Options>Text Editor>{Language}>Code Style>Formatting>"Choose When I paste, Indent, but do not format"

#include "StateMC_LockedOnSwordSwing.h"
#include "MainCharacter.h"
#include "CustomDefines.h"

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
}

void StateMC_LockedOnSwordSwing::Execute(float DeltaTime)
{
	//UE_LOG(LogTemp, Log, TEXT("Execute State StateMC_LockedOnSwordSwing"));
	//Setup moveVector

	//Check if we hit anything
	auto hitAI = Cast<ABaseAICharacter>(mainCharacter->weapon->overlappedPawn);
	if(!hitThisAttack && hitboxActive && hitAI)
	{
		hitThisAttack = true;
		hitAI->RecieveHit(10);
	}

	//Lerp to camera height
	//& Kick camera to the side for framing
	mainCharacter->cameraBoom->SetRelativeLocation(
		FVector (
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().X, mainCharacter->cameraLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().X, mainCharacter->cameraLerpAlpha * DeltaTime),
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Y, mainCharacter->cameraLockedHorizontalOffset * mainCharacter->cameraBoom->GetRightVector().Y, mainCharacter->cameraLerpAlpha * DeltaTime),
			FMath::Lerp(mainCharacter->cameraBoom->GetRelativeLocation().Z, mainCharacter->cameraLockedHeight, mainCharacter->cameraLerpAlpha * DeltaTime)
		)
	);
	
	//Rotate model towards the movement vector
	FVector dirToTarget = mainCharacter->lockedObject->GetActorLocation() - mainCharacter->GetActorLocation();
	dirToTarget.Z = 0;
	mainCharacter->Mesh->SetWorldRotation(FMath::Lerp(mainCharacter->Mesh->GetRelativeRotation(),  dirToTarget.Rotation(), FMath::Clamp( mainCharacter->attackTrackingIntensity * DeltaTime, DeltaTime, mainCharacter->attackTrackingIntensity)));
	
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

