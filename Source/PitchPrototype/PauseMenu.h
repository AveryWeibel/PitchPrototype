// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Settings.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMeditateDelegate);
UCLASS()
class PITCHPROTOTYPE_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite)
		bool bIsPaused;

	UPROPERTY(meta = (BindWidget))
		UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* ResumePanel;

	UPROPERTY(meta = (BindWidget))
		UButton* MeditateButton;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* MeditatePanel;

	UPROPERTY(meta = (BindWidget))
		UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
		USettings* SettingsWidget;

	UPROPERTY()
		bool settingsWasOpen;

	UPROPERTY(meta = (BindWidget))
		UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* MainMenuPanel;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* QuitPanel;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Title;

	UFUNCTION(BlueprintCallable)
		void PauseGame();

	UFUNCTION(BlueprintCallable)
		void UnpauseGame();

	UFUNCTION()
		void OnResumeButtonHovered();

	UFUNCTION()
		void OnResumeButtonUnhovered();

	UFUNCTION()
		void OnResumeButtonClicked();

	UFUNCTION()
		void OnMeditateButtonHovered();

	UFUNCTION()
		void OnMeditateButtonUnhovered();

	UFUNCTION()
		void OnMeditateButtonClicked();

	UFUNCTION()
		void OnSettingsButtonClicked();

	UFUNCTION()
		void OnMainMenuButtonHovered();

	UFUNCTION()
		void OnMainMenuButtonUnhovered();

	UFUNCTION()
		void OnMainMenuButtonClicked();

	UFUNCTION()
		void OnQuitGameButtonHovered();

	UFUNCTION()
		void OnQuitGameButtonUnhovered();

	UFUNCTION()
		void OnQuitGameButtonClicked();

	UFUNCTION()
		void HandleMeditate();

	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnMeditateDelegate OnMeditate;
};
