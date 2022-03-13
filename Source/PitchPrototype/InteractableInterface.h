// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractableInterface : public UInterface
{
 GENERATED_BODY()
};

class IInteractableInterface
{
 GENERATED_BODY()

public:
 UFUNCTION(BlueprintNativeEvent, Category="Interactable")
 void ReactToFocus();

 UFUNCTION(BlueprintNativeEvent, Category="Interactable")
 void ReactToUnFocus();

 UFUNCTION(BlueprintNativeEvent, Category="Interactable")
 void WhileFocused();

 UFUNCTION(BlueprintNativeEvent, Category="Interactable")
 void PlayerLock();

 UFUNCTION(BlueprintNativeEvent, Category="Interactable")
 void PlayerUnLock();

 UFUNCTION(BlueprintNativeEvent, Category="Interactable")
 void PlayerInteract();

 UFUNCTION(BlueprintNativeEvent, Category="Interactable")
 bool InteractToLockOn();
};
