// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "InteractableInterface.h"
#include "PropObject.generated.h"

UCLASS()
class PITCHPROTOTYPE_API APropObject : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APropObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UWidgetComponent* PromptWidgetComponent;

	void ReactToFocus_Implementation() override;

	void ReactToUnFocus_Implementation() override;

	void PlayerLock_Implementation() override;

	void PlayerUnLock_Implementation() override;

	void WhileFocused_Implementation() override;

	bool InteractToLockOn_Implementation() override;

};
