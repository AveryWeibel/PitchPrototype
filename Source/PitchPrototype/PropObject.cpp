// Fill out your copyright notice in the Description page of Project Settings.


#include "PropObject.h"

// Sets default values
APropObject::APropObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APropObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APropObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APropObject::ReactToFocus_Implementation()
{
	IInteractableInterface::ReactToFocus_Implementation();
}

void APropObject::ReactToUnFocus_Implementation()
{
	IInteractableInterface::ReactToUnFocus_Implementation();
}

void APropObject::PlayerLock_Implementation()
{
	IInteractableInterface::PlayerLock_Implementation();
}

void APropObject::PlayerUnLock_Implementation()
{
	IInteractableInterface::PlayerUnLock_Implementation();
}

void APropObject::WhileFocused_Implementation()
{
	IInteractableInterface::WhileFocused_Implementation();
}

bool APropObject::InteractToLockOn_Implementation()
{
	return IInteractableInterface::InteractToLockOn_Implementation();
}

