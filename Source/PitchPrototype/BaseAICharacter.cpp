// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAICharacter.h"
#include "BaseAIController.h"
#include "MainCharacter.h"
#include "PrompWidget.h"
#include "Components/WidgetComponent.h"
#include "State_MainCharacter.h"

// Sets default values
ABaseAICharacter::ABaseAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PromptWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PromptWidget"));
	PromptWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseAICharacter::BeginPlay()
{
	Super::BeginPlay();

	AIMesh = FindComponentByClass<USkeletalMeshComponent>();

	//TArray<UActorComponent*> components = GetComponentsByClass(UWidgetComponent::StaticClass);

	TArray<UActorComponent*> components = GetComponentsByClass(UWidgetComponent::StaticClass());

	for (auto it : components) {
		UDialogueSystem* temp = Cast<UDialogueSystem>(Cast<UWidgetComponent>(it)->GetWidget());
		if (temp) {
			dialogueSystem = temp;
			UE_LOG(LogTemp, Log, TEXT("dialogue system %s for %s"), *dialogueSystem->GetName(), *this->GetName());
			break;
		}
	}

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
	
	//UE_LOG(LogTemp, Log, TEXT("See Player"))
	if(AIController)
	{
		//UE_LOG(LogTemp, Log, TEXT("Valid Controller"))
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

	if (!canDodge) {
		DodgeCooldownElapsedTime = this->GetWorld()->GetTimeSeconds() - DodgeCooldownStartTime;

		if (DodgeCooldownElapsedTime >= dodgeCooldown) {
			canDodge = true;
		}
	}

	if (DodgeStartedTime > 0) {
		DodgeElapsedTime = this->GetWorld()->GetTimeSeconds() - DodgeStartedTime;

		DodgeDirection.Normalize();
		DodgeMoveVelocity += DodgeDirection * dodgeSpeed * DeltaTime;
		this->AddActorWorldOffset(DodgeMoveVelocity * DeltaTime);

		if (DodgeElapsedTime >= dodgeTime) {
			DodgeMoveVelocity = FVector::ZeroVector;
			DodgeStartedTime = -1;
		}
	}
}

// Called to bind functionality to input
void ABaseAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseAICharacter::RecieveHit(float damage)
{
	health -= damage;
	AIHealthChange();

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

void ABaseAICharacter::RecieveParry()
{
	ABaseAIController* AIController = Cast<ABaseAIController>(GetController());
	if (AIController)
	{
		AIController->UpdateState(TidesStateName::AI_ParryStun, Animator);
	}
}

void ABaseAICharacter::Dodge()
{
	UE_LOG(Log171General, Log, TEXT("Dodged Player Attack"));
	if (canDodge) {
		DodgeStartedTime = this->GetWorld()->GetTimeSeconds();
		DodgeDirection = this->GetActorRightVector() * (FMath::RandBool() ? 1 : -1);

		DodgeCooldownStartTime = DodgeStartedTime;
		canDodge = false;
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
	if(!CanTakeWaterDamage) {return;}
	
	health -= damage;
	AIHealthChange();

	if (health <= 0)
	{
		Die();
		return;
	}
}

void ABaseAICharacter::ReactToFocus_Implementation()
{
	IInteractableInterface::ReactToFocus_Implementation();
	Cast<UPrompWidget>(PromptWidgetComponent->GetWidget())->DisplayLockOnPrompt();
	Cast<UPrompWidget>(PromptWidgetComponent->GetWidget())->DisplayInteractPrompt();
	UE_LOG(Log171General, Log, TEXT("Focused %s"), *this->GetName());
}

void ABaseAICharacter::ReactToUnFocus_Implementation()
{
	IInteractableInterface::ReactToUnFocus_Implementation();
	Cast<UPrompWidget>(PromptWidgetComponent->GetWidget())->RemoveLockOnPrompt();
	Cast<UPrompWidget>(PromptWidgetComponent->GetWidget())->RemoveInteractPrompt();
	UE_LOG(Log171General, Log, TEXT("UnFocused %s"), *this->GetName());
}

void ABaseAICharacter::PlayerLock_Implementation()
{
	IInteractableInterface::PlayerLock_Implementation();
	UE_LOG(Log171General, Log, TEXT("Locked %s"), *this->GetName());
	PlayerLockBP();
}

void ABaseAICharacter::PlayerUnLock_Implementation()
{
	IInteractableInterface::PlayerUnLock_Implementation();
	UE_LOG(Log171General, Log, TEXT("UnLocked %s"), *this->GetName());
	PlayerUnLockBP();
}

void ABaseAICharacter::WhileFocused_Implementation()
{
	IInteractableInterface::WhileFocused_Implementation();
}

bool ABaseAICharacter::InteractToLockOn_Implementation()
{
	return true;
}

