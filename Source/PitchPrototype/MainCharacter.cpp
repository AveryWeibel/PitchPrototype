// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "StateMC_NonCombatMove.h"
#include "StateMC_NonCombatInAir.h"
#include "StateMC_NonCombatJump.h"
#include "CustomDefines.h"

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

	//Create instances of state sub-classes
	StateMC_NonCombatMove* NonCombatMove = new StateMC_NonCombatMove(this);
	StateMC_NonCombatInAir* NonCombatInAir = new StateMC_NonCombatInAir(this);
	StateMC_NonCombatJump* NonCombatJump = new StateMC_NonCombatJump(this);
	//Add all to array
	characterStateInstances.Add(NonCombatMove);
	characterStateInstances.Add(NonCombatInAir);
	characterStateInstances.Add(NonCombatJump);
	//Initialize state machine
	characterStateMachine = new StateMachine(characterStateInstances, StateName::NonCombatMove);


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

	check(IsValid(bodyCollider));
	check(IsValid(feetCollider));

	//bodyHitDelegate.BindUFunction(this, FName("HandleBodyHit"));

	//Bind ComponentHit events
	bodyCollider->OnComponentHit.AddDynamic(this, &AMainCharacter::HandleBodyHit);
	feetCollider->OnComponentHit.AddDynamic(this, &AMainCharacter::HandleFeetHit);

	//Bind ComponentOverlap events
	FScriptDelegate ComponentBeginOverlapDelegate;
	ComponentBeginOverlapDelegate.BindUFunction(this, "HandleFeetBeginOverlap");

	feetOverlap->OnComponentBeginOverlap.Add(ComponentBeginOverlapDelegate);

	FScriptDelegate ComponentEndOverlapDelegate;
	ComponentEndOverlapDelegate.BindUFunction(this, "HandleFeetEndOverlap");

	feetOverlap->OnComponentEndOverlap.Add(ComponentEndOverlapDelegate);

	//TODO read delegate documentation againnnn
	//feetOverlap->OnComponentBeginOverlap.Add(&AMainCharacter::HandleFeetBeginOverlap);

	//Bind Component
	//bodyCollider->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::HandleBodyHit);
	//feetCollider->OnComponentHit.AddDynamic(this, &AMainCharacter::HandleFeetHit);

	velocityArrow = FindComponentByClass<UArrowComponent>();

	print(Mesh->GetName());
	print(feetCollider->GetName());
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Run the execute function for the currently active state
	characterStateMachine->Execute(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
}

void AMainCharacter::MoveForward(float Value)
{
	characterStateMachine->SendInput(StateAction::MoveForward, Value);
}

void AMainCharacter::MoveRight(float Value)
{
	characterStateMachine->SendInput(StateAction::MoveRight, Value);
}

void AMainCharacter::Jump()
{
	characterStateMachine->SendInput(StateAction::Jump);
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
