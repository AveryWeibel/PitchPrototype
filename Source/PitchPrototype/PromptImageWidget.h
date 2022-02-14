// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "PromptImageWidget.generated.h"

/**
 * 
 */
UCLASS()
class PITCHPROTOTYPE_API UPromptImageWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Category = Prompts, BlueprintReadWrite, meta = (BindWidget))
		UImage* PromptImage;
};
