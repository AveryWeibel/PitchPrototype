// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "PromptImageWidget.h"
#include "PrompWidget.generated.h"

/**
 * 
 */
UCLASS()
class PITCHPROTOTYPE_API UPrompWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(Category = Prompts, BlueprintReadWrite, meta = (BindWidget))
		UHorizontalBox* PromptHorizontalBox;
	/*
	* 0 - Interact Prompt
	* 1 - Lock On Prompt
	*/
	UPROPERTY(Category = Prompts, BlueprintReadWrite)
		TArray<TSubclassOf<UUserWidget>> promptList;

	UPROPERTY(Category = Prompts, BlueprintReadWrite)
		TMap<FString, UUserWidget*> activePrompts;

	UFUNCTION(Category = Prompts, BlueprintCallable)
		void DisplayInteractPrompt();

	UFUNCTION(Category = Prompts, BlueprintCallable)
		void DisplayLockOnPrompt();
	
	UFUNCTION(Category = Prompts, BlueprintCallable)
		void ClearPrompts();

	UFUNCTION(Category = Prompts, BlueprintCallable)
		void RemoveInteractPrompt();

	UFUNCTION(Category = Prompts, BlueprintCallable)
		void RemoveLockOnPrompt();

	UFUNCTION()
		void correctSizeAndFill(UHorizontalBoxSlot* boxSlot);
};
