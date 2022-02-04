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
		hitAI->RecieveHit();
	}

	//Rotate model towards the movement vector
	FVector dirToTarget = mainCharacter->lockedAI->GetActorLocation() - mainCharacter->GetActorLocation();
	dirToTarget.Z = 0;
	mainCharacter->Mesh->SetWorldRotation(FMath::Lerp(mainCharacter->Mesh->GetRelativeRotation(),  dirToTarget.Rotation(), 4 * DeltaTime));
	
}

void StateMC_LockedOnSwordSwing::AnimEnd()
{
	State_MainCharacter::AnimEnd();
	hitThisAttack = false;
	RequestStateChange(TidesStateName::LockedOnMove);
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

