// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAICharacter.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "MainCharacterAnimInstance.h"
#include "StateMachine.h"
#include "Weapon.h"
#include "Components/SphereComponent.h"
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

	friend class UMainCharacterAnimInstance;
	friend class State_MainCharacter;
	
public:
	// Sets default values for this pawn's properties
	AMainCharacter();

	UPROPERTY(Category = Character, EditAnywhere)
		UArrowComponent* velocityArrow;

	/** The main skeletal mesh associated with this Character (optional sub-object). */
	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadOnly)
		USkeletalMeshComponent* Mesh;

	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category = Character, EditAnywhere)
		UCapsuleComponent* feetCollider;

	/** The CapsuleComponent being used for ground collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category = Character, EditAnywhere)
		UCapsuleComponent* feetOverlap;

	/** The SphereComponent being used for AI range detection (by CharacterMovement).*/
	UPROPERTY(Category  = Chracter, EditAnywhere)
		USphereComponent* AIOverlap;

	UPROPERTY(Category = Character, EditAnywhere)
		UCapsuleComponent* bodyCollider;

	UPROPERTY(Category = Character, EditAnywhere)
		UCameraComponent* mainCamera;

	UPROPERTY(Category = Character, EditAnywhere)
		USpringArmComponent* cameraBoom;

	UPROPERTY(Category = Character, EditAnywhere)
		float waterDamageMultiplier;
	
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

	UPROPERTY(Category = Camera, EditAnywhere)
		float cameraAccelerationForce;
	
	//Value between 0 & 1
	UPROPERTY(Category = Camera, EditAnywhere)
		float cameraLerpAlpha;

	UPROPERTY(Category = Camera, EditAnywhere)
		float cameraLockedBoomLength;

	UPROPERTY(Category = Camera, EditAnywhere)
		float cameraUnLockedBoomLength;

	UPROPERTY(Category = Camera, EditAnywhere)
		float cameraLockedHeight;

	UPROPERTY(Category = Camera, EditAnywhere)
		float cameraUnLockedHeight;

	UPROPERTY(Category = Camera, EditAnywhere)
		float cameraLockedHorizontalOffset;

	UPROPERTY(Category = Camera, EditAnywhere)
		float cameraUnLockedHorizontalOffset;
		
    UPROPERTY(Category = Combat, EditAnywhere, BlueprintReadWrite)
        AWeapon* weapon;

	UPROPERTY(Category = Combat, EditAnywhere)
		float parryDistance;

	UPROPERTY(Category = Combat, EditAnywhere)
		float attackTrackingIntensity;

	UPROPERTY(Category = Combat, EditAnywhere)
		float takeHitMaxSpeed;

	//Properties for internal use
	UPROPERTY(Category = GroundMovement, BlueprintReadOnly)
		FVector currentPhysicsLinearVelocity;

	UPROPERTY()
		TSet<ABaseAICharacter*> AIList;

	UPROPERTY(BlueprintReadOnly)
		ABaseAICharacter* lockedAI = nullptr;

	//Animation
	UMainCharacterAnimInstance* Animator = nullptr;

	//Combat Properties
	UPROPERTY(Category = Combat, EditAnywhere, BlueprintReadWrite)
		float dodgeLength;

	UPROPERTY(Category = Combat, EditAnywhere, BlueprintReadWrite)
		float dodgeSpeed;
	
	UPROPERTY(Category = Combat, EditAnywhere, BlueprintReadWrite)
		float playerHealth;

	UPROPERTY(Category = Combat, EditAnywhere, BlueprintReadWrite)
		float playerMaxHealth;

	UFUNCTION(Category = Combat, BlueprintCallable)
		float takeDamage(float damageAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool inWater;

	UFUNCTION(BlueprintCallable)
		void takeWaterDamage(float damage);

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

	void LockOn();

	void Attack();

	void Parry();

	void Dodge();
	
	void RecieveAnimEndNotif();

	void RecieveAnimHitboxActive();

	void RecieveAnimHitboxInactive();

	UFUNCTION()
	void HandleBodyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void HandleFeetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void HandleFeetBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void HandleFeetEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void HandleAIBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void HandleAIEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void RagdollModel();

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
	UFUNCTION()
		void TakeWeaponHit(float damage);

	UFUNCTION(BlueprintImplementableEvent, Category="Dialogue")
		void NativeSetDialogueInt(const FString& name, int value);

	UFUNCTION(BlueprintImplementableEvent, Category="Dialogue")
		void NativeSetDialogueStr(const FString& name, const FString& value);

	UFUNCTION(BlueprintNativeEvent, Category="Dialogue")
		int NativeGetDialogueInt(const FString& name);
	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
