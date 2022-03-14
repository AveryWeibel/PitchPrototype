// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"

void UPauseMenu::NativeConstruct() {
	Super::NativeConstruct();

	ResumeButton->OnHovered.AddUniqueDynamic(this, &UPauseMenu::OnResumeButtonHovered);
	ResumeButton->OnUnhovered.AddUniqueDynamic(this, &UPauseMenu::OnResumeButtonUnhovered);
	ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnResumeButtonClicked);

	MeditateButton->OnHovered.AddUniqueDynamic(this, &UPauseMenu::OnMeditateButtonHovered);
	MeditateButton->OnUnhovered.AddUniqueDynamic(this, &UPauseMenu::OnMeditateButtonUnhovered);
	MeditateButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnMeditateButtonClicked);

	SettingsButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnSettingsButtonClicked);

	MainMenuButton->OnHovered.AddUniqueDynamic(this, &UPauseMenu::OnMainMenuButtonHovered);
	MainMenuButton->OnUnhovered.AddUniqueDynamic(this, &UPauseMenu::OnMainMenuButtonUnhovered);
	MainMenuButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnMainMenuButtonClicked);

	QuitGameButton->OnHovered.AddUniqueDynamic(this, &UPauseMenu::OnQuitGameButtonHovered);
	QuitGameButton->OnUnhovered.AddUniqueDynamic(this, &UPauseMenu::OnQuitGameButtonUnhovered);
	QuitGameButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnQuitGameButtonClicked);
}

void UPauseMenu::PauseGame()
{
	bIsPaused = true;
	APlayerController* player = UGameplayStatics::GetPlayerController(this, 0);

	this->AddToViewport();

	if (player) {
		player->SetPause(true);
		FInputModeUIOnly inputMode = FInputModeUIOnly::FInputModeUIOnly();
		inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
		player->SetInputMode(inputMode);
		player->bShowMouseCursor = true;
	}
}

void UPauseMenu::UnpauseGame()
{
	bIsPaused = false;
	APlayerController* player = UGameplayStatics::GetPlayerController(this, 0);

	player->SetPause(false);
	player->SetInputMode(FInputModeGameOnly());
	player->bShowMouseCursor = false;

	this->RemoveFromParent();
}

void UPauseMenu::OnResumeButtonHovered()
{
	ResumePanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UPauseMenu::OnResumeButtonUnhovered()
{
	ResumePanel->SetVisibility(ESlateVisibility::Collapsed);
	if (settingsWasOpen) {
		SettingsWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UPauseMenu::OnResumeButtonClicked()
{
	ResumePanel->SetVisibility(ESlateVisibility::Collapsed);
	if (settingsWasOpen) {
		SettingsWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	UnpauseGame();
}

void UPauseMenu::OnMeditateButtonHovered()
{
	MeditatePanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UPauseMenu::OnMeditateButtonUnhovered()
{
	MeditatePanel->SetVisibility(ESlateVisibility::Collapsed);
	if (settingsWasOpen) {
		SettingsWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UPauseMenu::OnMeditateButtonClicked()
{
	HandleMeditate();
}

void UPauseMenu::OnSettingsButtonClicked()
{
	if (SettingsWidget->GetVisibility() == ESlateVisibility::Collapsed) {
		SettingsWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		settingsWasOpen = true;
	}
	else 
	{
		SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
		settingsWasOpen = false;
	}
}

void UPauseMenu::OnMainMenuButtonHovered()
{
	MainMenuPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UPauseMenu::OnMainMenuButtonUnhovered()
{
	MainMenuPanel->SetVisibility(ESlateVisibility::Collapsed);
	if (settingsWasOpen) {
		SettingsWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UPauseMenu::OnMainMenuButtonClicked()
{
	UnpauseGame();
	UGameplayStatics::OpenLevel(this, FName::FName(TEXT("MainMenuMap")));
}

void UPauseMenu::OnQuitGameButtonHovered()
{
	QuitPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UPauseMenu::OnQuitGameButtonUnhovered()
{
	QuitPanel->SetVisibility(ESlateVisibility::Collapsed);
	if (settingsWasOpen) {
		SettingsWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UPauseMenu::OnQuitGameButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
}

void UPauseMenu::HandleMeditate()
{
	UnpauseGame();
	OnMeditate.Broadcast();
}
