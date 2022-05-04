// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAIController.h"
#include "InteractableInterface.h"
#include "TownGuardAnimInstance.h"
#include "Weapon.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "DialogueSystem.h"
#include "BaseAICharacter.generated.h"

UCLASS()
class PITCHPROTOTYPE_API ABaseAICharacter : public ACharacter, public IInteractableInterface
{
	GENERATED_BODY()

	friend class UTownGuardAnimInstance;
	friend class UTidesBTTaskNode;
	
public:
	// Sets default values for this character's properties
	ABaseAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "AI")
		UPawnSensingComponent* pawnSensingComp;

	UPROPERTY(BlueprintReadOnly)
		USkeletalMeshComponent* AIMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UWidgetComponent* PromptWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
		int health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	int weaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool inWater;

	UPROPERTY()
		bool IsDead;
	
	UFUNCTION()
		void OnSeePlayer(APawn *Pawn);

	//Blueprint callable, bound to ink function calls
	UFUNCTION(BlueprintCallable, Category="AIState")
		void StartCombat();

	UFUNCTION(BlueprintCallable, Category="AIAction")
		void DoAttack();

	UFUNCTION()
		void RecieveAnimEnd();
	
	UFUNCTION()
		void RecieveHitboxActive();

	UFUNCTION()
		void RecieveHitboxInactive();

	UFUNCTION()
		void Die();

	UFUNCTION(BlueprintImplementableEvent, Category="AIState")
		void RagdollAI();
		

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(BlueprintReadOnly)
	UTownGuardAnimInstance* Animator;

	UPROPERTY(Category = Combat, EditAnywhere, BlueprintReadWrite)
	AWeapon* Weapon;	
	
	UFUNCTION(BlueprintCallable, meta=(DisplayName = "RecieveHit"))
	void RecieveHit(float damage = 0);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AIParried"))
		void RecieveParry();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "AIHealthChange"))
		void AIHealthChange();
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "PlayerLockBP"))
	void PlayerLockBP();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "PlayerUnLockBP"))
	void PlayerUnLockBP();

	float DodgeCooldownStartTime;
	float DodgeCooldownElapsedTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
		float dodgeCooldown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
		bool canDodge;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
		float dodgeTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
		float dodgeSpeed;

	float DodgeStartedTime;
	float DodgeElapsedTime;
	FVector DodgeMoveVelocity;
	FVector DodgeDirection;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void Dodge();

	UFUNCTION()
		bool GetIsDead();
	UFUNCTION()
		float GetWeaponDamage();
	
	UFUNCTION(BlueprintCallable)
		void takeWaterDamage(float damage);

	void ReactToFocus_Implementation() override;

	void ReactToUnFocus_Implementation() override;

	void PlayerLock_Implementation() override;
	
	void PlayerUnLock_Implementation() override;

	void WhileFocused_Implementation() override;

	bool InteractToLockOn_Implementation() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue System")
		UDialogueSystem* dialogueSystem;
};
