// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMC_NonCombatMove.h"

// Call parent Ctor
StateMC_NonCombatMove::StateMC_NonCombatMove(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	stateName = StateName::NonCombatMove;
}

StateMC_NonCombatMove::~StateMC_NonCombatMove()
{
}

void StateMC_NonCombatMove::Start()
{
	//Testing code, temp temp temp
	if (stateName == StateName::NonCombatMove) {
		UE_LOG(LogTemp, Log, TEXT("Enter State %s"), *testStr);
	}
}

void StateMC_NonCombatMove::Execute(float deltatime)
{
	UE_LOG(LogTemp, Log, TEXT("Executingggggg %f"), deltatime);
}
