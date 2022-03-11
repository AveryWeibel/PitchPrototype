// Fill out your copyright notice in the Description page of Project Settings.


#include "TidesGameInstance.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

UTidesGameInstance::UTidesGameInstance() {
	loopCounter = 0;

	tutorialFinished = false;

	CameraSensitivity = 100.0f;
	fullscreen = false;
}

void UTidesGameInstance::setCameraSensitivity(float newSens)
{
	CameraSensitivity = newSens;

	AMainCharacter* player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	player->cameraAccelerationForce = CameraSensitivity;
}

void UTidesGameInstance::setFullScreen(bool newFullScreen)
{
	fullscreen = newFullScreen;
}
