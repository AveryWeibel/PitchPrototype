// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "TidesGameInstance.h"
#include "Engine/GameInstance.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Components\WidgetSwitcher.h"
#include "Components\Button.h"
#include "Settings.generated.h"

/**
 * 
 */
UCLASS()
class PITCHPROTOTYPE_API USettings : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* KeyboardButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UButton* ControllerButton;

	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* SettingsWidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* SettingsPanel;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UTextBlock* Title;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UTextBlock* GameplayTitle;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UTextBlock* FullScreenText;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UCheckBox* FullScreenCheckBox;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UTextBlock* CameraSensText;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		USlider* CameraSensBar;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UTextBlock* SoundTitle;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UTextBlock* MasterVolumeText;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		USlider* MasterVolumeBar;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UTextBlock* MusicVolumeText;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		USlider* MusicVolumeBar;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UTextBlock* SFXVolumeText;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		USlider* SFXVolumeBar;

	UFUNCTION(BlueprintCallable)
		void OnFullScreenCheckBoxClicked(bool isChecked);

	UFUNCTION(BlueprintCallable)
		void OnCameraSensBarChanged(float Value);

	UFUNCTION(BlueprintCallable)
		void OnMasterVolumeBarChanged(float Value);

	UFUNCTION(BlueprintCallable)
		void OnMusicVolumeBarChanged(float Value);

	UFUNCTION(BlueprintCallable)
		void OnSFXVolumeBarChanged(float Value);

	UFUNCTION(BlueprintCallable)
		void onControllerButtonClicked();

	UFUNCTION(BlueprintCallable)
		void onKeyboardButtonClicked();

	UFUNCTION(BlueprintCallable)
		void onSettingsButtonClicked();

private:

	UPROPERTY()
		UGameUserSettings* settings;

	UPROPERTY()
		UTidesGameInstance* gameInstance;

	UFUNCTION()
		void syncSettings(ESlateVisibility type);

	void NativeConstruct() override;
};
