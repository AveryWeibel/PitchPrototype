// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TidesGameInstance.generated.h"

/**
 * 
 */
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
		// NPC name -> json string
		TMap<FString, FString> NPCDictionary;

	UPROPERTY(Category = TidesGameInstance, EditAnywhere, BlueprintReadWrite)
		//if you finished the tutorial
		bool tutorialFinished;


};
