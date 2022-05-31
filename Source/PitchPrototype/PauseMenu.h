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

	UPROPERTY(BlueprintReadWrite)
		TArray<UButton*> ButtonList;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* ResumePanel;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* MeditateButton;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* MeditatePanel;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		USettings* SettingsWidget;

	UPROPERTY()
		bool settingsWasOpen;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* MainMenuPanel;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* QuitPanel;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Title;

	UFUNCTION(BlueprintCallable)
		void PauseGame();

	UFUNCTION(BlueprintCallable)
		void UnpauseGame();

	UFUNCTION(BlueprintCallable)
		void OnResumeButtonHovered();

	UFUNCTION(BlueprintCallable)
		void OnResumeButtonUnhovered();

	UFUNCTION(BlueprintCallable)
		void OnResumeButtonClicked();

	UFUNCTION(BlueprintCallable)
		void OnMeditateButtonHovered();

	UFUNCTION(BlueprintCallable)
		void OnMeditateButtonUnhovered();

	UFUNCTION(BlueprintCallable)
		void OnMeditateButtonClicked();

	UFUNCTION(BlueprintCallable)
		void OnSettingsButtonClicked();

	UFUNCTION(BlueprintCallable)
		void OnSettingsButtonHovered();

	UFUNCTION(BlueprintCallable)
		void OnSettingsButtonUnhovered();

	UFUNCTION(BlueprintCallable)
		void OnMainMenuButtonHovered();

	UFUNCTION(BlueprintCallable)
		void OnMainMenuButtonUnhovered();

	UFUNCTION(BlueprintCallable)
		void OnMainMenuButtonClicked();

	UFUNCTION(BlueprintCallable)
		void OnQuitGameButtonHovered();

	UFUNCTION(BlueprintCallable)
		void OnQuitGameButtonUnhovered();

	UFUNCTION(BlueprintCallable)
		void OnQuitGameButtonClicked();

	UFUNCTION()
		void HandleMeditate();

	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnMeditateDelegate OnMeditate;
};
