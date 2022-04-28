// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainCharacter.h"
#include "TidesGameInstance.generated.h"
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FMasterVolumeDelegate, float, newVolume);
DECLARE_MULTICAST_DELEGATE_OneParam(FSFXVolumeDelegate, float, newVolume);

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

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnMasterVolumeChanged"))
		FMasterVolumeDelegate OnMasterVolumeDelegate;
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnSFXVolumeChanged"))
		FSFXVolumeDelegate OnSFXVolumeDelegate;

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		//keeps track of number of loops
		int loopCounter;

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		// NPC name -> variable state
		TMap<FString, FNPCVariables> NPCDictionary;

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		//if you finished the tutorial
		bool tutorialFinished;

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		bool canReadRunes;

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		bool killedSpellcaster;

	//SETTINGS*******************************************************************SETTINGS
	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		float CameraSensitivity;
	
	UFUNCTION(Category = TidesGameInstance, BlueprintCallable)
		void setCameraSensitivity(float newSens);

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		bool fullscreen;

	UFUNCTION(Category = TidesGameInstance, BlueprintCallable)
		void setFullScreen(bool newFullScreen);

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		float MasterVolume;

	UFUNCTION(Category = TidesGameInstance, BlueprintCallable)
		void setMasterVolume(float newVolume);

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		float SFXVolume;

	UFUNCTION(Category = TidesGameInstance, BlueprintCallable)
		void setSFXVolume(float newVolume);
};
