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

	UPROPERTY(meta = (BindWidget))
		UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
		UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget))
		USettings* SettingsWidget;

	UPROPERTY(meta = (BindWidget))
		UButton* CreditsButton;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* CreditsPanel;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Title;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TeamName;

	UFUNCTION()
		void OnPlayButtonClicked();

	UFUNCTION()
		void OnOptionsButtonClicked();

	UFUNCTION()
		void OnCreditsButtonClicked();

	UFUNCTION()
		void OnQuitButtonClicked();

	void NativeConstruct() override;
};
