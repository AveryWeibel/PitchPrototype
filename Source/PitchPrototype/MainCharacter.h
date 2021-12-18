// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCharacter.generated.h"

//Forward declare components
class UCapsuleComponent;
class USekeletalMeshComponent;
class UArrowComponent;

UCLASS()
class PITCHPROTOTYPE_API AMainCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainCharacter();

	UPROPERTY(Category = Character, EditAnywhere)
		UArrowComponent* velocityArrow;

	/** The main skeletal mesh associated with this Character (optional sub-object). */
	UPROPERTY(Category = Character, EditAnywhere)
		USkeletalMeshComponent* Mesh;

	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category = Character, EditAnywhere)
		UCapsuleComponent* CapsuleComponent;

	UPROPERTY(Category = Movement, EditAnywhere)
		float accelerationForce;

	UPROPERTY(Category = Movement, EditAnywhere)
		float jumpForce;

	UPROPERTY(Category = Movement, EditAnywhere)
		float jumpDirectionalMultiplier;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called for Jump input */
	void Jump();

private:
	FVector* movementVector = new FVector();
	float moveX = 0;
	float moveY = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
