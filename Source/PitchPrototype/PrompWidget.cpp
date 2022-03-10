// Fill out your copyright notice in the Description page of Project Settings.


#include "PrompWidget.h"

#include "MainCharacter.h"

void UPrompWidget::DisplayInteractPrompt() {
	UE_LOG(Log171General, Log, TEXT("Display Interact"));
	UUserWidget* prompt = CreateWidget(this, promptList[0]);
	UHorizontalBoxSlot* slot = PromptHorizontalBox->AddChildToHorizontalBox(prompt);
	correctSizeAndFill(slot);

	activePrompts.Add("InteractPrompt", prompt);
}

void UPrompWidget::DisplayLockOnPrompt() {
	UE_LOG(Log171General, Log, TEXT("Display LockOn"));
	UUserWidget* prompt = CreateWidget(this, promptList[1]);
	UHorizontalBoxSlot* slot = PromptHorizontalBox->AddChildToHorizontalBox(prompt);
	correctSizeAndFill(slot);

	activePrompts.Add("LockOnPrompt", prompt);
}

void UPrompWidget::RemoveInteractPrompt() {
	UE_LOG(Log171General, Log, TEXT("Remove Interact"));
	PromptHorizontalBox->RemoveChild(activePrompts["InteractPrompt"]);

	activePrompts.Remove("InteractPrompt");
}

void UPrompWidget::RemoveLockOnPrompt() {
	UE_LOG(Log171General, Log, TEXT("Remove LockOn"));
	PromptHorizontalBox->RemoveChild(activePrompts["LockOnPrompt"]);

	activePrompts.Remove("LockOnPrompt");
}

void UPrompWidget::ClearPrompts() {
	PromptHorizontalBox->ClearChildren();

	activePrompts.Empty();
}

void UPrompWidget::correctSizeAndFill(UHorizontalBoxSlot* boxSlot) {
	FSlateChildSize size = FSlateChildSize(ESlateSizeRule::Fill);
	size.Value = 1.0f;

	boxSlot->SetSize(size);
	boxSlot->SetHorizontalAlignment(EHorizontalAlignment(HAlign_Center));
	boxSlot->SetVerticalAlignment(EVerticalAlignment(HAlign_Center));
}