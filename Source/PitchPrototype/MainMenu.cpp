// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "TidesGameInstance.h"
#include "Components/CanvasPanelSlot.h"

void UMainMenu::NativeConstruct() {
	Super::NativeConstruct();

	PlayButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnPlayButtonClicked);
	OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnOptionsButtonClicked);
	CreditsButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnCreditsButtonClicked);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnQuitButtonClicked);

	ButtonList.AddUnique(PlayButton);
	ButtonList.AddUnique(OptionsButton);
	ButtonList.AddUnique(CreditsButton);
	ButtonList.AddUnique(QuitButton);
}

void UMainMenu::OnPlayButtonClicked() {
	UGameplayStatics::OpenLevel(this, FName::FName(TEXT("MainMap")));
}

void UMainMenu::OnOptionsButtonClicked() {
	if (SettingsWidget->GetVisibility() == ESlateVisibility::Collapsed) {
		SettingsWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		CreditsPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	
}

void UMainMenu::OnCreditsButtonClicked() {
	if (CreditsPanel->GetVisibility() == ESlateVisibility::Collapsed) {
		CreditsPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else 
	{
		CreditsPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainMenu::OnQuitButtonClicked() {
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
}