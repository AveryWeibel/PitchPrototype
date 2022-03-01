// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* StartButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* OptionsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* CreditsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* QuitButton;

	UFUNCTION()
		void OnStartButtonClicked();

	UFUNCTION()
		void OnOptionsButtonClicked();

	UFUNCTION()
		void OnCreditsButtonClicked();

	UFUNCTION()
		void OnQuitButtonClicked();

	void NativeConstruct() override;
};
