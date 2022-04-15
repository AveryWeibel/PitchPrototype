// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

void UMainMenu::NativeConstruct() {
	Super::NativeConstruct();

	ContinueButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnContinueButtonClicked);
	NewGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnNewGameButtonClicked);
	OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnOptionsButtonClicked);
	CreditsButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnCreditsButtonClicked);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnQuitButtonClicked);
}

void UMainMenu::OnContinueButtonClicked() {

}

void UMainMenu::OnNewGameButtonClicked() {
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