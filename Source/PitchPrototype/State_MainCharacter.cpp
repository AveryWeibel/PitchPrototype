// Fill out your copyright notice in the Description page of Project Settings.


#include "State_MainCharacter.h"

State_MainCharacter::State_MainCharacter(AMainCharacter* mainCharacterPtr)
{
	mainCharacter = mainCharacterPtr;
	check(mainCharacter);
}

State_MainCharacter::~State_MainCharacter()
{
}

