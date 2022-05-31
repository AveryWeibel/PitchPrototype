// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "BaseAICharacter.h"
#include "StateMC_NonCombatMove.h"
#include "StateMC_NonCombatInAir.h"
#include "StateMC_NonCombatJump.h"
#include "CustomDefines.h"
#include "StateMC_Dead.h"
#include "StateMC_Intro.h"
#include "StateMC_InWater.h"
#include "StateMC_LockedOnDodge.h"
#include "StateMC_LockedOnMove.h"
#include "StateMC_LockedOnSwordSwing.h"
#include "StateMC_LockedOnTakeHit.h"
#include "StateMC_LockedOnDodge.h"

DEFINE_LOG_CATEGORY(Log171General);

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	Mesh = FindComponentByClass<USkeletalMeshComponent>();	

	TArray<UCapsuleComponent*> capsuleCollisions;

	//Bind input delegates to state machine
	//MoveForwardDelegate.BindRaw(characterStateMachine, SendInput(StateAction));


	//Get all our capsules
	GetComponents<UCapsuleComponent>(capsuleCollisions);

	//Assign the correct ones to their accessors
	for (auto caps : capsuleCollisions)
	{
		if (caps->ComponentHasTag(FName("BodyCap"))) {
			bodyCollider = caps;
		}
	}

	AIOverlap = FindComponentByClass<USphereComponent>();

	check(IsValid(AIOverlap));
	check(IsValid(bodyCollider));

	//bodyHitDelegate.BindUFunction(this, FName("HandleBodyHit"));

	//Bind ComponentHit events
	bodyCollider->OnComponentHit.AddDynamic(this, &AMainCharacter::HandleBodyHit);

	//Bind ComponentOverlap events

	//Bind AI BeginOverlap
	FScriptDelegate AIBeginOverlapDelegate;
	AIBeginOverlapDelegate.BindUFunction(this, "HandleAIBeginOverlap");
	AIOverlap->OnComponentBeginOverlap.Add(AIBeginOverlapDelegate);

	//Bind AI EndOverlap
	FScriptDelegate AIEndOverlapDelegate;
	AIEndOverlapDelegate.BindUFunction(this, "HandleAIEndOverlap");
	AIOverlap->OnComponentEndOverlap.Add(AIEndOverlapDelegate);

	velocityArrow = FindComponentByClass<UArrowComponent>();

	mainCamera = FindComponentByClass<UCameraComponent>();

	cameraBoom = FindComponentByClass<USpringArmComponent>();

	Animator = Cast<UMainCharacterAnimInstance>(Mesh->GetAnimInstance());

    //Initialize states last so all the references they have in player are vaild
	//Create instances of state sub-classes
	StateMC_NonCombatMove* NonCombatMove = new StateMC_NonCombatMove(this);
	StateMC_NonCombatInAir* NonCombatInAir = new StateMC_NonCombatInAir(this);
	StateMC_NonCombatJump* NonCombatJump = new StateMC_NonCombatJump(this);
	StateMC_LockedOnMove* LockedOnMove = new StateMC_LockedOnMove(this);
	StateMC_LockedOnSwordSwing* LockedOnSwordSwing = new StateMC_LockedOnSwordSwing(this);
	StateMC_LockedOnTakeHit* LockedOnTakeHit = new StateMC_LockedOnTakeHit(this);
	StateMC_LockedOnDodge* LockedOnDodge = new StateMC_LockedOnDodge(this);
	StateMC_Dead* Dead = new StateMC_Dead(this);
	StateMC_InWater* InWater = new StateMC_InWater(this);
	StateMC_Intro* Intro = new StateMC_Intro(this);
	//Add all to array
	characterStateInstances.Add(NonCombatMove);
	characterStateInstances.Add(NonCombatInAir);
	characterStateInstances.Add(NonCombatJump);
	characterStateInstances.Add(LockedOnMove);
	characterStateInstances.Add(LockedOnSwordSwing);
	characterStateInstances.Add(LockedOnTakeHit);
	characterStateInstances.Add(LockedOnDodge);
	characterStateInstances.Add(Dead);
	characterStateInstances.Add(InWater);
	characterStateInstances.Add(Intro);
	
	//Initialize state machine
	characterStateMachine = new StateMachine(characterStateInstances, TidesStateName::Intro);

	//Combat Initialization
	playerMaxHealth = 100.0f;
	playerHealth = playerMaxHealth;

	// FRotator storedMeshRot = Mesh->GetComponentRotation();
	//
	if(bodyCollider->GetComponentRotation().Yaw != 0)
	{
		bodyCollider->SetWorldRotation(FRotator::ZeroRotator);
	}
	//
	// Mesh->SetWorldRotation(storedMeshRot);
} //End BeginPlay

int AMainCharacter::NativeGetDialogueInt_Implementation(const FString& name)
{
	UE_LOG(Log171General, Error, TEXT("Called C++ implementation of NativeGetDialogueInt(), this should never happen"))
	return INT_MAX;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Run the execute function for the currently active state
	characterStateMachine->Execute(DeltaTime);

	//Debug
	currentPhysicsLinearVelocity = bodyCollider->GetPhysicsLinearVelocity();

	velocityArrow->SetRelativeRotation(horizontalVelocity.Rotation());
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpRate);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &AMainCharacter::LockOn);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainCharacter::Attack);
	PlayerInputComponent->BindAction("Parry", IE_Pressed, this, &AMainCharacter::Parry);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AMainCharacter::Dodge);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::ToggleSprint);
	PlayerInputComponent->BindAction("Sheathe", IE_Pressed, this, &AMainCharacter::Sheathe);
}

StateMachine* AMainCharacter::GetStateMachine()
{
	return characterStateMachine;
}

void AMainCharacter::EnterWater()
{
	characterStateMachine->SendInput(StateAction::EnterWater);
}

void AMainCharacter::ExitWater()
{
	characterStateMachine->SendInput(StateAction::ExitWater);	
}

void AMainCharacter::TakeWeaponHit(float damage)
{
	if(!(characterStateMachine->GetActiveStateName() == TidesStateName::LockedOnDodging))
		takeDamage(damage);
	
	if(playerHealth <= 0)
	{
		characterStateMachine->SendInput(StateAction::Die);
	}
	else
	{
		characterStateMachine->SendInput(StateAction::TakeHit);
	}
}

void AMainCharacter::MoveForward(float Value)
{
	characterStateMachine->SendInput(StateAction::MoveForward, Value);
}

void AMainCharacter::MoveRight(float Value)
{
	characterStateMachine->SendInput(StateAction::MoveRight, Value);
}

void AMainCharacter::TurnRate(float Value)
{
	characterStateMachine->SendInput(StateAction::TurnRate, Value);
}

void AMainCharacter::LookUpRate(float Value)
{
	characterStateMachine->SendInput(StateAction::LookUpRate, Value);
}

void AMainCharacter::Jump()
{
	characterStateMachine->SendInput(StateAction::Jump);
}

void AMainCharacter::LockOn()
{
	characterStateMachine->SendInput(StateAction::LockOn);
}

void AMainCharacter::ToggleSprint()
{
	characterStateMachine->SendInput(StateAction::ToggleSprint);
}

void AMainCharacter::Attack()
{
	characterStateMachine->SendInput(StateAction::DoAttack);
}

void AMainCharacter::Parry()
{
	characterStateMachine->SendInput(StateAction::Parry);
}

void AMainCharacter::Dodge()
{
	characterStateMachine->SendInput(StateAction::Dodge);
}

void AMainCharacter::Interact()
{
	characterStateMachine->SendInput(StateAction::Interact);
}

void AMainCharacter::Sheathe()
{
	characterStateMachine->SendInput(StateAction::Sheathe);
}

void AMainCharacter::RecieveAnimEndNotif()
{
	characterStateMachine->SendInput(StateAction::AnimEnd);
}

void AMainCharacter::RecieveAnimHitboxActive()
{
	characterStateMachine->SendInput(StateAction::AnimHitboxActive);
}

void AMainCharacter::RecieveAnimHitboxInactive()
{
	characterStateMachine->SendInput(StateAction::AnimHitboxInactive);
}

void AMainCharacter::IntroAnimEnd()
{
	if(characterStateMachine)
	{
		characterStateMachine->SendInput(StateAction::EndIntroAnim);
	}
}

void AMainCharacter::StartIntroMontage()
{
	Animator->StartIntroMontage();
}

void AMainCharacter::HandleBodyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	print("Hit Body");
}

void AMainCharacter::HandleFeetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(Log171General, Log, TEXT("Hit with %s"), *OtherActor->GetName())
	characterStateMachine->SendInput(StateAction::OverlapFeet, *OtherActor);
}

void AMainCharacter::HandleFeetBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(Log171General, Log, TEXT("Began Overlap with %s"), *OtherActor->GetName())
		characterStateMachine->SendInput(StateAction::OverlapFeet, *OtherActor);
}

void AMainCharacter::HandleFeetEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(Log171General, Log, TEXT("Stopped Overlap with %s"), *OtherActor->GetName())
		characterStateMachine->SendInput(StateAction::EndOverlapFeet, *OtherActor);
}

void AMainCharacter::HandleAIBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		InteractableList.Add(OtherActor);
		UE_LOG(Log171General, Log, TEXT("Began AI Overlap with %s"), *OtherActor->GetName());
	}
}

void AMainCharacter::HandleAIEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(InteractableList.Find(OtherActor))
	{
		InteractableList.Remove(OtherActor);
		//UE_LOG(Log171General, Log, TEXT("Stopped AI Overlap with %s"), *OtherActor->GetName());
	}

	/*ABaseAICharacter* character = Cast<ABaseAICharacter>(OtherActor);
	ABaseAIController* controller = Cast<ABaseAIController>(character->GetController());

	if (controller) {
		TidesStateName state = controller->GetState();

		if (state == TidesStateName::AI_CombatStrafe || state == TidesStateName::AI_CombatDialogue || state == TidesStateName::AI_CombatDialogueWait) {
			controller->UpdateState(TidesStateName::AI_NonCombatIdle, character->Animator);
		}
	}*/

	characterStateMachine->SendInput(StateAction::EndOverlapAI);
}

float AMainCharacter::takeDamage(float damageAmount) {
	playerHealth -= damageAmount;

	UE_LOG(Log171General, Log, TEXT("Player taking %f damage"), damageAmount);

	PlayerTakeDamage();

	if (playerHealth <= 0.0f) {
		playerHealth = 0.0f;
		characterStateMachine->SendInput(StateAction::Die);
	}

	return damageAmount;
}

void AMainCharacter::takeWaterDamage(float damage) {
	playerHealth -= (damage * waterDamageMultiplier);

	PlayerTakeDamage();

	if(playerHealth <= 0)
	{
		characterStateMachine->SendInput(StateAction::Die);
	}
}
