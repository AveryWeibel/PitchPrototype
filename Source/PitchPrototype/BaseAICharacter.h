// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAIController.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "BaseAICharacter.generated.h"

UCLASS()
class PITCHPROTOTYPE_API ABaseAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UPawnSensingComponent* pawnSensingComp;
	
	UFUNCTION()
	void OnSeePlayer(APawn *Pawn);

	UFUNCTION(BlueprintCallable, Category="AIState")
		void StartCombat();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "PlayerLock"))
	void PlayerLock();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "PlayerUnLock"))
	void PlayerUnLock();

	
};
