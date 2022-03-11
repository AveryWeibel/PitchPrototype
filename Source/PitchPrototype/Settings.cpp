// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings.h"

void USettings::NativeConstruct() {
	Super::NativeConstruct();

	settings = UGameUserSettings::GetGameUserSettings();
	gameInstance = Cast<UTidesGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	FullScreenCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &USettings::OnFullScreenCheckBoxClicked);
	CameraSensBar->OnValueChanged.AddUniqueDynamic(this, &USettings::OnCameraSensBarChanged);
	MasterVolumeBar->OnValueChanged.AddUniqueDynamic(this, &USettings::OnMasterVolumeBarChanged);
	SFXVolumeBar->OnValueChanged.AddUniqueDynamic(this, &USettings::OnSFXVolumeBarChanged);

	this->OnVisibilityChanged.AddUniqueDynamic(this, &USettings::syncSettings);
}

void USettings::syncSettings(ESlateVisibility type) {
	if (type == ESlateVisibility::SelfHitTestInvisible) {
		gameInstance->fullscreen ? FullScreenCheckBox->SetCheckedState(ECheckBoxState::Checked) : FullScreenCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
		CameraSensBar->SetValue(gameInstance->CameraSensitivity);
		MasterVolumeBar->SetValue(gameInstance->MasterVolume);
		SFXVolumeBar->SetValue(gameInstance->SFXVolume);
	}
	else
	{

	}
}

void USettings::OnFullScreenCheckBoxClicked(bool isChecked) {
	if (isChecked) {
		settings->SetScreenResolution(FIntPoint::FIntPoint(1920, 1080));
		UE_LOG(LogTemp, Log, TEXT("Setting to Fullscreen"));
	}
	else 
	{
		settings->SetScreenResolution(FIntPoint::FIntPoint(1280, 720));
		UE_LOG(LogTemp, Log, TEXT("Setting to Windowed"));
	}

	gameInstance->setFullScreen(isChecked);
	settings->ApplySettings(false);
}

void USettings::OnCameraSensBarChanged(float Value) {
	gameInstance->setCameraSensitivity(Value);
}

void USettings::OnMasterVolumeBarChanged(float Value) {

}

void USettings::OnSFXVolumeBarChanged(float Value) {

}

