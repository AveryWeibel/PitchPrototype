// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings.h"

void USettings::NativeConstruct() {
	Super::NativeConstruct();

	settings = UGameUserSettings::GetGameUserSettings();
	gameInstance = Cast<UTidesGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	FullScreenCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &USettings::OnFullScreenCheckBoxClicked);
	CameraSensBar->OnValueChanged.AddUniqueDynamic(this, &USettings::OnCameraSensBarChanged);
	MasterVolumeBar->OnValueChanged.AddUniqueDynamic(this, &USettings::OnMasterVolumeBarChanged);
	MusicVolumeBar->OnValueChanged.AddUniqueDynamic(this, &USettings::OnMusicVolumeBarChanged);
	SFXVolumeBar->OnValueChanged.AddUniqueDynamic(this, &USettings::OnSFXVolumeBarChanged);

	ControllerButton->OnClicked.AddUniqueDynamic(this, &USettings::onControllerButtonClicked);
	KeyboardButton->OnClicked.AddUniqueDynamic(this, &USettings::onKeyboardButtonClicked);
	SettingsButton->OnClicked.AddUniqueDynamic(this, &USettings::onSettingsButtonClicked);

	this->OnVisibilityChanged.AddUniqueDynamic(this, &USettings::syncSettings);

	bIsFocusable = true;
}

void USettings::syncSettings(ESlateVisibility type) {
	if (type == ESlateVisibility::SelfHitTestInvisible) {
		gameInstance->fullscreen ? FullScreenCheckBox->SetCheckedState(ECheckBoxState::Checked) : FullScreenCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
		CameraSensBar->SetValue(gameInstance->CameraSensitivity);
		MasterVolumeBar->SetValue(gameInstance->MasterVolume);
		MusicVolumeBar->SetValue(gameInstance->MusicVolume);
		SFXVolumeBar->SetValue(gameInstance->SFXVolume);
	}
	else
	{

	}
}

void USettings::onSettingsButtonClicked()
{
	SettingsWidgetSwitcher->SetActiveWidgetIndex(0);
}

void USettings::onKeyboardButtonClicked()
{
	SettingsWidgetSwitcher->SetActiveWidgetIndex(1);
}

void USettings::onControllerButtonClicked()
{
	SettingsWidgetSwitcher->SetActiveWidgetIndex(2);
}

void USettings::OnFullScreenCheckBoxClicked(bool isChecked) {
	if (isChecked) {
		settings->SetScreenResolution(FIntPoint::FIntPoint(1920, 1080));
		settings->SetFullscreenMode(EWindowMode::Fullscreen);
		//UE_LOG(LogTemp, Log, TEXT("Setting to Fullscreen"));
	}
	else 
	{
		settings->SetScreenResolution(FIntPoint::FIntPoint(1280, 720));
		settings->SetFullscreenMode(EWindowMode::Windowed);
		//UE_LOG(LogTemp, Log, TEXT("Setting to Windowed"));
	}

	gameInstance->setFullScreen(isChecked);
	settings->ApplySettings(false);
}

void USettings::OnCameraSensBarChanged(float Value) {
	gameInstance->setCameraSensitivity(Value);
}

void USettings::OnMasterVolumeBarChanged(float Value) {
	gameInstance->setMasterVolume(Value);
}

void USettings::OnMusicVolumeBarChanged(float Value)
{
	gameInstance->setMusicVolume(Value);
}

void USettings::OnSFXVolumeBarChanged(float Value) {
	gameInstance->setSFXVolume(Value);
}

