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

