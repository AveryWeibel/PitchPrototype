// Copyright Epic Games, Inc. All Rights Reserved.

#include "PitchPrototypeGameMode.h"
#include "PitchPrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

APitchPrototypeGameMode::APitchPrototypeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/PrototypeCharacter/MainCharacterBP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
