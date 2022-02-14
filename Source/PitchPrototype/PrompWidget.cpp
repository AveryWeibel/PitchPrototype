// Fill out your copyright notice in the Description page of Project Settings.


#include "PrompWidget.h"

void UPrompWidget::DisplayInteractPrompt() {
	UUserWidget* prompt = CreateWidget(this, promptList[0]);
	UHorizontalBoxSlot* slot = PromptHorizontalBox->AddChildToHorizontalBox(prompt);
	correctSizeAndFill(slot);

	activePrompts.Add("InteractPrompt", prompt);
}

void UPrompWidget::DisplayLockOnPrompt() {
	UUserWidget* prompt = CreateWidget(this, promptList[1]);
	UHorizontalBoxSlot* slot = PromptHorizontalBox->AddChildToHorizontalBox(prompt);
	correctSizeAndFill(slot);

	activePrompts.Add("LockOnPrompt", prompt);
}

void UPrompWidget::RemoveInteractPrompt() {
	PromptHorizontalBox->RemoveChild(activePrompts["InteractPrompt"]);

	activePrompts.Remove("InteractPrompt");
}

void UPrompWidget::RemoveLockOnPrompt() {
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