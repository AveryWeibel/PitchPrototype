// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TidesGameInstance.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FNPCVariables {
	GENERATED_BODY()

		UPROPERTY(Category = NPCVariables, EditAnywhere, BlueprintReadWrite)
		TMap<FString, FString> VariableState;
};

UCLASS(Blueprintable)
class PITCHPROTOTYPE_API UTidesGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UTidesGameInstance();

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		//keeps track of number of loops
		int loopCounter;

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		// NPC name -> variable state
		TMap<FString, FNPCVariables> NPCDictionary;

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		//if you finished the tutorial
		bool tutorialFinished;

	//SETTINGS*******************************************************************SETTINGS
	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		float CameraSensitivity;

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		bool fullscreen;

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		float MasterVolume;

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		float SFXVolume;
};
