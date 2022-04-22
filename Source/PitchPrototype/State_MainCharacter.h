// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"

DECLARE_LOG_CATEGORY_EXTERN(Log171MainCharState, Log, All);

class AMainCharacter;

/**
 * In-Between class that delcares and assigns variables and objects that it's subclasses will manipulate
 */

class PITCHPROTOTYPE_API State_MainCharacter : public State
{
	friend class StateMachine;

public:
	State_MainCharacter(AMainCharacter*);
	~State_MainCharacter();

	//Dictionary<MainCharacterActions, StateAxisDelegate> StateAxisDelegates;
	//Dictionary<MainCharacterActions, StateActionDelegate> StateActionDelegates;

protected:
	//State overrides
	void RequestStateChange(TidesStateName) override;
	
	//Variables/Objects managed by this state
	AMainCharacter* mainCharacter;

	FVector* movementVector = new FVector(FVector::ZeroVector);
	FRotator* cameraTurnVector = new FRotator(FRotator::ZeroRotator);
	bool grounded = false;

	//Move Inputs
	float moveFwd = 0;
	float moveRht = 0;
	float moveZ = 0;
	FVector storedMovement;

	//Camera variables
	FRotator cameraRotationLerpTarget;
	FRotator cameraBoomRotationLerpTarget;
	float cameraBoomTargetLength;

	//Camera Inputs
	float cameraFrontThreshold = 0.95f;

	//Functions for managed variables
	void ConsumeMoveInputs();
	void ConsumeCameraInput(float DeltaTime);
	void AddCameraOrbitYaw(float Value);
	void AddCameraOrbitPitch(float Value);
	bool IsInCameraView(FVector);
	void MoveCameraLocked(float DeltaTime, FVector dirToTarget, float speedMod = 1);
	void RagdollModel();
	void CallInteractBP();

	//Implement State SendInput
	void SendInput(StateAction) override;
	void SendInput(StateAction, float) override;

	//SubClass variables
	AActor* focusedInteractable = nullptr;
	
	//SubClass functions
	
	//Check for any interactables in range and determine which one to highlight
	void SweepForInteractables();
	
	//Input delegate methods
	//Empty definitions here so that subclasses don't all have to implement them
	virtual void MoveForward(float);
	virtual void MoveRight(float);
	virtual void TurnRate(float);
	virtual void LookUpRate(float);
	virtual void AnimEnd();
	virtual void AnimHitboxActive();
	virtual void AnimHitboxInactive();
	virtual void Jump();
	virtual void LockOn();
	virtual void DoAttack();
	virtual void Parry();
	virtual void Dodge();
	virtual void TakeHit();
	virtual void Die();
	virtual void Interact();
	virtual void BeginOverlapFeet();
	virtual void EndOverlapFeet();
	virtual void StartOverlapAI();
	virtual void EndOverlapAI();
};