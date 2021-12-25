// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "StateMachine.h"
#include "MainCharacter.generated.h"

//Forward declare components
class State;

DECLARE_LOG_CATEGORY_EXTERN(Log171General, Log, All);

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
		UCapsuleComponent* feetCollider;

	UPROPERTY(Category = Character, EditAnywhere)
		UCapsuleComponent* bodyCollider;

	UPROPERTY(Category = Movement, EditAnywhere)
		float accelerationForce;

	UPROPERTY(Category = Movement, EditAnywhere)
		float maximumHorizontalVelocity;

	UPROPERTY(Category = Movement, EditAnywhere)
		float jumpForce;

	UPROPERTY(Category = Movement, EditAnywhere)
		float jumpDirectionalMultiplier;

	UPROPERTY(Category = Movement, EditAnywhere)
		float gravityAmount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called for Jump input */
	void Jump();

	UFUNCTION()
	void HandleBodyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void HandleFeetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	//Character locomotion state variables
	FVector* movementVector = new FVector(FVector::ZeroVector);
	float moveX = 0;
	float moveY = 0;
	float moveZ = 0;
	bool grounded = false;

	void ApplyGravity(float gravityAccel);

	StateMachine* characterStateMachine;
	TArray<State*> characterStateInstances;

	TScriptDelegate<FWeakObjectPtr> bodyHitDelegate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
