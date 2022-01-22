// Fill out your copyright notice in the Description page of Project Settings.

//SETTINGS IN VISUAL STUDIO 2022
//Tools>Options>Text Editor>{Language}>Code Style>Formatting>"Choose When I paste, Indent, but do not format"

#include "<ClassName>.h"
#include "MainCharacter.h"
#include "CustomDefines.h"

<ClassName>::<ClassName>(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	//Add new entry to StateName in State.h
	//stateName = StateName::<EnumName>;
}

<ClassName>::~<ClassName>()
{
}

void <ClassName>::Start()
{
	UE_LOG(LogTemp, Log, TEXT("Enter State <ClassName>"));
}

void <ClassName>::Execute(float DeltaTime)
{
	//UE_LOG(LogTemp, Log, TEXT("Execute State <ClassName>"));
	//Setup moveVector	

	ConsumeMoveInputs();

	//Apply moveVector
}

