// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

void UMainMenu::NativeConstruct() {
	Super::NativeConstruct();

	StartButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnStartButtonClicked);
	OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnOptionsButtonClicked);
	CreditsButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnCreditsButtonClicked);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnQuitButtonClicked);
}

void UMainMenu::OnStartButtonClicked() {
	UGameplayStatics::OpenLevel(this, FName::FName(TEXT("MainMap")));
}

void UMainMenu::OnOptionsButtonClicked() {

}

void UMainMenu::OnCreditsButtonClicked() {

}

void UMainMenu::OnQuitButtonClicked() {
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
}