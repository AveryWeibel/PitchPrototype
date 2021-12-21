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
			feetCollider = caps;
		}
		else if (caps->ComponentHasTag(FName("BodyCap"))) {
			bodyCollider = caps;
		}
	}

	check(IsValid(bodyCollider));
	check(IsValid(feetCollider));

	//bodyHitDelegate.BindUFunction(this, FName("HandleBodyHit"));

	bodyCollider->OnComponentHit.AddDynamic(this, &AMainCharacter::HandleBodyHit);
	feetCollider->OnComponentHit.AddDynamic(this, &AMainCharacter::HandleBodyHit);

	velocityArrow = FindComponentByClass<UArrowComponent>();

	print(Mesh->GetName());
	print(feetCollider->GetName());
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ApplyGravity(-9.81);


	movementVector->Set(moveX, moveY, moveZ);


	//printFString("X: %f", feetCollider->GetPhysicsLinearVelocity().X);
	//printFString("Y: %f", feetCollider->GetPhysicsLinearVelocity().Y);
	//printFString("Z: %f", feetCollider->GetPhysicsLinearVelocity().Z);

	feetCollider->SetWorldRotation(FRotator(0,0,0));
	feetCollider->SetPhysicsLinearVelocity(*movementVector);
	//feetCollider->AddForce(*movementVector);

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
	feetCollider->AddImpulse( FVector(movementVector->X * jumpDirectionalMultiplier, movementVector->Y * jumpDirectionalMultiplier, jumpForce) );
}

void AMainCharacter::HandleBodyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	print("Hit Something");
	UE_LOG(Pla, Log, TEXT("ImpactNormal[X: %f, Y: %f, Z: %f]"), Hit.ImpactNormal.X, Hit.ImpactNormal.Y, Hit.ImpactNormal.Z);
	moveX -= Hit.ImpactNormal.X;
	moveY -= Hit.ImpactNormal.Y;
	moveZ += Hit.ImpactNormal.Z;
}

void AMainCharacter::ApplyGravity(float gravityAccel)
{
	moveZ += gravityAccel;
}