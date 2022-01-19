// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAICharacter.h"
#include "BaseAIController.h"

// Sets default values
ABaseAICharacter::ABaseAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ABaseAICharacter::BeginPlay()
{
	Super::BeginPlay();

	pawnSensingComp = FindComponentByClass<UPawnSensingComponent>();

	UE_LOG(LogTemp, Log, TEXT("AI begin play"))
	
	if(pawnSensingComp)
	{
		UE_LOG(LogTemp, Log, TEXT("Bind on see player"))
		pawnSensingComp->OnSeePawn.AddDynamic(this, &ABaseAICharacter::OnSeePlayer);
	}
}

void ABaseAICharacter::OnSeePlayer(APawn* Pawn)
{
	ABaseAIController* AIController = Cast<ABaseAIController>(GetController());
	
	UE_LOG(LogTemp, Log, TEXT("See Player"))
	if(AIController)
	{
		UE_LOG(LogTemp, Log, TEXT("Valid Controller"))
		AIController->SetMoveTarget(Pawn->GetActorLocation());
	}
	 
}

// Called every frame
void ABaseAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

