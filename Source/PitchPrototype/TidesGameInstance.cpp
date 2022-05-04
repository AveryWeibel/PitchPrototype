// Fill out your copyright notice in the Description page of Project Settings.


#include "TidesGameInstance.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

UTidesGameInstance::UTidesGameInstance() {
	loopCounter = 0;

	tutorialFinished = false;
	canReadRunes = false;

	CameraSensitivity = 100.0f;
	MasterVolume = 0.5f;
	SFXVolume = 0.5f;
	fullscreen = false;
}

void UTidesGameInstance::setCameraSensitivity(float newSens)
{
	CameraSensitivity = newSens;

	AMainCharacter* player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (player) {
		player->cameraAccelerationForce = CameraSensitivity;
	}

	//UE_LOG(LogTemp, Log, TEXT("New Camera Sens: %d"), newSens);
}

void UTidesGameInstance::setFullScreen(bool newFullScreen)
{
	fullscreen = newFullScreen;
}

void UTidesGameInstance::setMasterVolume(float newVolume)
{
	MasterVolume = newVolume;
	MasterVolumeChanged(MasterVolume);
	//UE_LOG(LogTemp, Log, TEXT("New Master Volume: %d"), newVolume);
}

void UTidesGameInstance::setSFXVolume(float newVolume)
{
	SFXVolume = newVolume;
	SFXVolumeChanged(SFXVolume);
	//UE_LOG(LogTemp, Log, TEXT("New SFX Volume: %d"), newVolume);
}
