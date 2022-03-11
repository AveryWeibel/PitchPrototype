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
#include "Settings.generated.h"

/**
 * 
 */
UCLASS()
class PITCHPROTOTYPE_API USettings : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* SettingsPanel;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Title;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* GameplayTitle;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* FullScreenText;

	UPROPERTY(meta = (BindWidget))
		UCheckBox* FullScreenCheckBox;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CameraSensText;

	UPROPERTY(meta = (BindWidget))
		USlider* CameraSensBar;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* SoundTitle;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* MasterVolumeText;

	UPROPERTY(meta = (BindWidget))
		USlider* MasterVolumeBar;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* SFXVolumeText;

	UPROPERTY(meta = (BindWidget))
		USlider* SFXVolumeBar;

	UFUNCTION(BlueprintCallable)
		void OnFullScreenCheckBoxClicked(bool isChecked);

	UFUNCTION(BlueprintCallable)
		void OnCameraSensBarChanged(float Value);

	UFUNCTION(BlueprintCallable)
		void OnMasterVolumeBarChanged(float Value);

	UFUNCTION(BlueprintCallable)
		void OnSFXVolumeBarChanged(float Value);

private:

	UPROPERTY()
		UGameUserSettings* settings;

	UPROPERTY()
		UTidesGameInstance* gameInstance;

	UFUNCTION()
		void syncSettings(ESlateVisibility type);

	void NativeConstruct() override;
};
