// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Settings.h"
#include "UObject/UObjectGlobals.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PITCHPROTOTYPE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite)
		TArray<UButton*> ButtonList;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* PlayButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget))
		USettings* SettingsWidget;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* CreditsButton;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* CreditsPanel;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Title;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TeamName;

	UFUNCTION(BlueprintCallable)
		void OnPlayButtonClicked();

	UFUNCTION(BlueprintCallable)
		void OnOptionsButtonClicked();

	UFUNCTION(BlueprintCallable)
		void OnCreditsButtonClicked();

	UFUNCTION(BlueprintCallable)
		void OnQuitButtonClicked();

	void NativeConstruct() override;
};
