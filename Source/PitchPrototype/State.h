// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum TidesStateName {
	NonCombatMove,
	NonCombatInAir,
	NonCombatJump,
	LockedOnMove,
	SwordAttack,
	LockedOnDodging,
	LockedOnTakeHit,
	Dead,
	InWater,
	AI_AttemptAttack,
	AI_CombatStrafe,
	AI_DoAttack,
	AI_CombatDialogue,
	AI_NonCombatIdle,
	AI_NonCombatPatrol,
	AI_Dialogue,
	AI_RecieveHit,
	AI_ParryStun,
	AI_Dodge,
	AI_CombatDialogueWait,
	AI_Dead
};


enum StateAction 
{ 
	MoveForward,
	MoveRight,
	Jump,
	DoAttack,
	Parry,
	Dodge,
	OverlapFeet, 
	EndOverlapFeet, 
	TurnRate,
	LookUpRate,
	LockOn,
	AnimEnd,
	TakeHit,
	Die,
	ToggleSprint,
	Interact,
	AnimHitboxActive,
	AnimHitboxInactive,
	StartOverlapAI,
	EndOverlapAI,
	EnterWater,
	ExitWater
};

class StateMachine;

/**
 * Abstract state class
 * Custom state child classes implemented as needed
 */
class PITCHPROTOTYPE_API State
{
	friend class StateMachine;

	typedef void (* NewFunction)(float);

public:
	State();
	virtual  ~State();
	TidesStateName GetStateName();

protected:

	//Attempts to change the state to given StateName
	virtual void RequestStateChange(TidesStateName);

	//Fundamental state Overrides
	virtual void Start() = 0;
	virtual void Execute(float) = 0;

	//Input function dispatchers
	virtual void SendInput(StateAction Action) = 0;
	virtual void SendInput(StateAction Action, float Value) = 0;
	virtual void SendInput(StateAction Action, AActor& OtherActor) = 0;

	TMap<StateAction, NewFunction> StateAxisDelegates;

	TidesStateName stateName;

protected:
	StateMachine* parentStateMachine;
};