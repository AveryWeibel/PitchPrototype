// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAIController.h"
#include "TownGuardAnimInstance.h"
#include "Weapon.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "BaseAICharacter.generated.h"

UCLASS()
class PITCHPROTOTYPE_API ABaseAICharacter : public ACharacter
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
	void RecieveHit();
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "PlayerLock"))
	void PlayerLock();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "PlayerUnLock"))
	void PlayerUnLock();

	
};
