// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMC_NonCombatInAir.h"
#include "MainCharacter.h"
#include "CustomDefines.h"

StateMC_NonCombatInAir::StateMC_NonCombatInAir(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	stateName = TidesStateName::NonCombatInAir;
}

StateMC_NonCombatInAir::~StateMC_NonCombatInAir()
{
}

void StateMC_NonCombatInAir::Start()
{
	UE_LOG(LogTemp, Log, TEXT("Enter State NonCombatInAir"));
}

void StateMC_NonCombatInAir::Execute(float DeltaTime)
{
	//UE_LOG(LogTemp, Log, TEXT("Execute State NonCombatInAir"));
	//apply movement inputs for this frame
	ApplyGravity();

	mainCharacter->feetCollider->AddForce(*movementVector);

	mainCharacter->feetCollider->SetWorldRotation(FRotator(0, 0, 0));
}

void StateMC_NonCombatInAir::BeginOverlapFeet()
{
	print("Hit Feets");

	//Zero out vertical actual velocity and vertical input velocity
	mainCharacter->feetCollider->SetPhysicsLinearVelocity(FVector(mainCharacter->currentPhysicsLinearVelocity.X, mainCharacter->currentPhysicsLinearVelocity.Y, 0));
	gravityAccumulation = 0;

	RequestStateChange(TidesStateName::NonCombatMove);
}

void StateMC_NonCombatInAir::ApplyGravity()
{
	//New comments
	gravityAccumulation -= mainCharacter->fallingGravityAmount;
//	moveZ = gravityAccumulation;
}