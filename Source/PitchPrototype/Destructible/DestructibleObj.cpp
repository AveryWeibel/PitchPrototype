// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "DestructibleObj.h"

// Sets default values
ADestructibleObj::ADestructibleObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible Component"));
	DestructibleComponent->SetupAttachment(RootComponent);
	//Simulation Generates Hit Events toggle on
	DestructibleComponent->SetNotifyRigidBodyCollision(true);

	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component"));
	TriggerComponent->SetupAttachment(RootComponent);

	isDestroyed = false;
	isTriggerEnabled = false;

	maxHealth = 10.f;

	defaultDamage = 1.f;
	defaultImpulse = 1.f;

}

// Called when the game starts or when spawned
void ADestructibleObj::BeginPlay()
{
	Super::BeginPlay();

	DestructibleComponent->OnComponentHit.AddDynamic(this, &ADestructibleObj::Damage);
	
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ADestructibleObj::Trigger);

	currentHealth = maxHealth;
	
}

// Called every frame
void ADestructibleObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

