// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "StateMachine.h"
#include "MainCharacter.generated.h"

//Forward declare components
class State;
class State_MainCharacter;

//Declare Macros
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
		UCapsuleComponent* feetOverlap;

	UPROPERTY(Category = Character, EditAnywhere)
		UCapsuleComponent* bodyCollider;

	UPROPERTY(Category = Character, EditAnywhere)
		UCameraComponent* mainCamera;

	UPROPERTY(Category = Character, EditAnywhere)
		USpringArmComponent* cameraBoom;

	UPROPERTY(Category = GroundMovement, EditAnywhere)
		float accelerationForce;

	UPROPERTY(Category = GroundMovement, EditAnywhere)
		float maximumHorizontalVelocity;

	UPROPERTY(Category = Jumping, EditAnywhere)
		float jumpForce;

	UPROPERTY(Category = Jumping, EditAnywhere)
		float jumpDirectionalMultiplier;

	UPROPERTY(Category = Jumping, EditAnywhere)
		float risingGravityAmount;

	UPROPERTY(Category = Jumping, EditAnywhere)
		float fallingGravityAmount;

	//Properties for internal use
	UPROPERTY(Category = GroundMovement, BlueprintReadOnly)
		FVector currentPhysicsLinearVelocity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void TurnRate(float Value);

	void LookUpRate(float Value);

	/** Called for Jump input */
	void Jump();

	UFUNCTION()
	void HandleBodyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void HandleFeetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void HandleFeetBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void HandleFeetEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	//Character locomotion state variables

	//void ApplyGravity(float gravityAccel);

	StateMachine* characterStateMachine;
	TArray<State*> characterStateInstances;


	//Create input delegates for state machine
	StateAxisDelegate MoveForwardDelegate;

	//Create collision delegates
	TScriptDelegate<FWeakObjectPtr> bodyHitDelegate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
