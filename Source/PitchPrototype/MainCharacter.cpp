// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"

//Credit from https://unrealcpp.com/debug-logging/
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT(text), fstring))

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
	
	//Get all our capsules
	GetComponents<UCapsuleComponent>(capsuleCollisions);

	//Assign the correct ones to their accessors
	for (auto caps : capsuleCollisions)
	{
		if (caps->ComponentHasTag(FName("GroundCap"))) {
			CapsuleComponent = caps;
		}
	}

	check(IsValid(CapsuleComponent));

	//bodyHitDelegate.BindUFunction(this, FName("HandleBodyHit"));

	CapsuleComponent->OnComponentHit.AddDynamic(this, &AMainCharacter::HandleBodyHit);

	velocityArrow = FindComponentByClass<UArrowComponent>();

	print(Mesh->GetName());
	print(CapsuleComponent->GetName());
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ApplyGravity(-9.81);

	movementVector->Set(moveX, moveY, moveZ);

	//printFString("X: %f", CapsuleComponent->GetPhysicsLinearVelocity().X);
	//printFString("Y: %f", CapsuleComponent->GetPhysicsLinearVelocity().Y);
	//printFString("Z: %f", CapsuleComponent->GetPhysicsLinearVelocity().Z);

	CapsuleComponent->SetPhysicsLinearVelocity(*movementVector);
	//CapsuleComponent->AddForce(*movementVector * accelerationForce);

	//movementVector->Set(0, 0, 0);
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
	
	moveX = Value * accelerationForce;

}

void AMainCharacter::MoveRight(float Value)
{
	moveY = Value * accelerationForce;
}

void AMainCharacter::Jump()
{
	print("Jump");
	CapsuleComponent->AddImpulse( FVector(movementVector->X * jumpDirectionalMultiplier, movementVector->Y * jumpDirectionalMultiplier, jumpForce) );
}

void AMainCharacter::HandleBodyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	print("Hit Something");
}

void AMainCharacter::ApplyGravity(float gravityAccel)
{
	moveZ += gravityAccel;
}