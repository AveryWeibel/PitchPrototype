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

	AIMesh = FindComponentByClass<USkeletalMeshComponent>();	

	pawnSensingComp = FindComponentByClass<UPawnSensingComponent>();

	UE_LOG(LogTemp, Log, TEXT("AI begin play"))
	
	if(pawnSensingComp)
	{
		UE_LOG(LogTemp, Log, TEXT("Bind on see player"))
		pawnSensingComp->OnSeePawn.AddDynamic(this, &ABaseAICharacter::OnSeePlayer);
	}

	Animator = Cast<UTownGuardAnimInstance>(AIMesh->GetAnimInstance());
}

void ABaseAICharacter::OnSeePlayer(APawn* Pawn)
{
	ABaseAIController* AIController = Cast<ABaseAIController>(GetController());
	
	UE_LOG(LogTemp, Log, TEXT("See Player"))
	if(AIController)
	{
		UE_LOG(LogTemp, Log, TEXT("Valid Controller"))
		AIController->SetMoveTarget(Pawn->GetActorLocation());
		//AIController->UpdateState(TidesStateName::AI_NonCombatIdle, Animator);
	}
	 
}

void ABaseAICharacter::StartCombat()
{
	ABaseAIController* AIController = Cast<ABaseAIController>(GetController());
	if(AIController)
	{
		AIController->UpdateState(TidesStateName::AI_CombatStrafe, Animator);
	}
}

void ABaseAICharacter::DoAttack()
{
	UE_LOG(Log171GuardAI, Log, TEXT("DoAttack()"));
	ABaseAIController* AIController = Cast<ABaseAIController>(GetController());
	if(AIController)
	{
		AIController->UpdateState(TidesStateName::AI_DoAttack, Animator);
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

void ABaseAICharacter::RecieveHit(float damage)
{
	health -= damage;
	if(health <= 0)
	{
		Die();
		return;
	}
	
	ABaseAIController* AIController = Cast<ABaseAIController>(GetController());
	if(AIController)
	{
		AIController->UpdateState(TidesStateName::AI_RecieveHit, Animator);
	}
}

bool ABaseAICharacter::GetIsDead()
{
	return IsDead;
}

float ABaseAICharacter::GetWeaponDamage()
{
	return weaponDamage;
}

void ABaseAICharacter::RecieveAnimEnd()
{
	ABaseAIController* AIController = Cast<ABaseAIController>(GetController());
	if(AIController)
	{
		AIController->SetAnimEndBool(true);
	}
}

void ABaseAICharacter::RecieveHitboxActive()
{
	ABaseAIController* AIController = Cast<ABaseAIController>(GetController());
	if(AIController)
	{
		AIController->SetHitboxActive(true);
	}
}

void ABaseAICharacter::RecieveHitboxInactive()
{
	ABaseAIController* AIController = Cast<ABaseAIController>(GetController());
	if(AIController)
	{
		AIController->SetHitboxActive(false);
	}
}

void ABaseAICharacter::Die()
{
	ABaseAIController* AIController = Cast<ABaseAIController>(GetController());
	if(AIController)
	{
		AIController->UpdateState(TidesStateName::AI_Dead, Animator);
		RagdollAI();
		IsDead = true;
		AIController->BehaviorComp->StopTree();
	}
}

void ABaseAICharacter::takeWaterDamage(float damage) {
	health -= damage;

	if (health <= 0)
	{
		Die();
		return;
	}
}

