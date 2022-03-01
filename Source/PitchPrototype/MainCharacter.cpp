// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "BaseAICharacter.h"
#include "StateMC_NonCombatMove.h"
#include "StateMC_NonCombatInAir.h"
#include "StateMC_NonCombatJump.h"
#include "CustomDefines.h"
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
		if (caps->ComponentHasTag(FName("GroundCap"))) {
			feetCollider = caps;
		}
		else if (caps->ComponentHasTag(FName("BodyCap"))) {
			bodyCollider = caps;
		}
		else if (caps->ComponentHasTag(FName("FeetOverlapCap"))) {
			feetOverlap = caps;
		}
	}

	AIOverlap = FindComponentByClass<USphereComponent>();

	check(IsValid(AIOverlap));
	check(IsValid(bodyCollider));
	check(IsValid(feetCollider));

	//bodyHitDelegate.BindUFunction(this, FName("HandleBodyHit"));

	//Bind ComponentHit events
	bodyCollider->OnComponentHit.AddDynamic(this, &AMainCharacter::HandleBodyHit);
	feetCollider->OnComponentHit.AddDynamic(this, &AMainCharacter::HandleFeetHit);

	//Bind ComponentOverlap events
	//Bind Feet BeginOverlap
	FScriptDelegate FeetBeginOverlapDelegate;
	FeetBeginOverlapDelegate.BindUFunction(this, "HandleFeetBeginOverlap");
	feetOverlap->OnComponentBeginOverlap.Add(FeetBeginOverlapDelegate);

	//Bind Feet EndOverlap
	FScriptDelegate FeetEndOverlapDelegate;
	FeetEndOverlapDelegate.BindUFunction(this, "HandleFeetEndOverlap");
	feetOverlap->OnComponentEndOverlap.Add(FeetEndOverlapDelegate);

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
	//Add all to array
	characterStateInstances.Add(NonCombatMove);
	characterStateInstances.Add(NonCombatInAir);
	characterStateInstances.Add(NonCombatJump);
	characterStateInstances.Add(LockedOnMove);
	characterStateInstances.Add(LockedOnSwordSwing);
	characterStateInstances.Add(LockedOnTakeHit);
	characterStateInstances.Add(LockedOnDodge);
	//Initialize state machine
	characterStateMachine = new StateMachine(characterStateInstances, TidesStateName::NonCombatMove);

	//Combat Initialization
	playerMaxHealth = 100.0f;
	playerHealth = 100.0f;

	print(Mesh->GetName());
	print(feetCollider->GetName());
}

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
	currentPhysicsLinearVelocity = feetCollider->GetPhysicsLinearVelocity();

	velocityArrow->SetWorldRotation(currentPhysicsLinearVelocity.Rotation());
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
}

void AMainCharacter::TakeWeaponHit()
{
	takeDamage(10);
	characterStateMachine->SendInput(StateAction::TakeHit);
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

void AMainCharacter::HandleBodyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	print("Hit Body");
}

void AMainCharacter::HandleFeetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	characterStateMachine->SendInput(StateAction::BeginOverlapFeet);
}

void AMainCharacter::HandleFeetBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(Log171General, Log, TEXT("Began Overlap with %s"), *OtherActor->GetName())
		characterStateMachine->SendInput(StateAction::BeginOverlapFeet);
}

void AMainCharacter::HandleFeetEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(Log171General, Log, TEXT("Stopped Overlap with %s"), *OtherActor->GetName())
		characterStateMachine->SendInput(StateAction::EndOverlapFeet);
}

void AMainCharacter::HandleAIBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(const auto AIActor = Cast<ABaseAICharacter>(OtherActor))
	{
		AIList.Add(AIActor);
		UE_LOG(Log171General, Log, TEXT("Began AI Overlap with %s"), *OtherActor->GetName());
	}
}

void AMainCharacter::HandleAIEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(const auto AIActor =  Cast<ABaseAICharacter>(OtherActor))
	{
		AIList.Remove(AIActor);
		//UE_LOG(Log171General, Log, TEXT("Stopped AI Overlap with %s"), *OtherActor->GetName());
	}
}

float AMainCharacter::takeDamage(float damageAmount) {
	playerHealth -= damageAmount;

	UE_LOG(Log171General, Log, TEXT("Player taking %f damage"), damageAmount);

	if (playerHealth < 0.0f) {
		playerHealth = 0.0f;
	}

	return damageAmount;
}

void AMainCharacter::takeWaterDamage(float damage) {
	playerHealth -= damage;
}
