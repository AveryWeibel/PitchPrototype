// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMC_NonCombatInAir.h"
#include "MainCharacter.h"
#include "CustomDefines.h"

StateMC_NonCombatInAir::StateMC_NonCombatInAir(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	stateName = TidesStateName::NonCombatInAir;
}

StateMC_NonCombatInAir::~StateMC_NonCombatInAir()
{
}

void StateMC_NonCombatInAir::Start()
{
	UE_LOG(LogTemp, Log, TEXT("Enter State NonCombatInAir"));
	gravityAccumulation = 0;
	JumpDirMultiplierAlpha = 0;

	//Set Ground Trace Params
	if(mainCharacter)
	{
		groundTraceParams.AddIgnoredActor(mainCharacter);
		//GroundTraceResponseParams.DefaultResponseParam.
	}
}

void StateMC_NonCombatInAir::Execute(float DeltaTime)
{
	//apply movement inputs for this frame
	JumpDirMultiplierAlpha = FMath::Lerp(1.0f, mainCharacter->jumpDirectionalMultiplier, FMath::Clamp<float>(mainCharacter->jumpDirMultiplierRampSpeed * DeltaTime, mainCharacter->jumpDirectionalMultiplier, 1));
	
	//ApplyGravity();
	UE_LOG(Log171General, Log, TEXT("MovementVectorInAir: X: %f Y: %f Z: %f"), movementVector->X, movementVector->Y, movementVector->Z);
	
	MoveCharacter(DeltaTime);

	mainCharacter->feetCollider->SetWorldRotation(FRotator(0, mainCharacter->feetCollider->GetComponentRotation().Yaw, 0));
	*movementVector = FVector::ZeroVector;
}

void StateMC_NonCombatInAir::BeginOverlapFeet()
{
	print("Hit Feets");

	//Zero out vertical actual velocity and vertical input velocity
	gravityAccumulation = 0;
	JumpDirMultiplierAlpha = 0;
	//movementVector->Z = 0;
	mainCharacter->feetCollider->SetPhysicsLinearVelocity(FVector(0, 0, mainCharacter->feetCollider->GetPhysicsLinearVelocity().Z));

	RequestStateChange(TidesStateName::NonCombatMove);
}

void StateMC_NonCombatInAir::ApplyGravity()
{
	//New comments
	if (FMath::Abs(movementVector->Z) < mainCharacter->maxFallingSpeed)
	{
		gravityAccumulation -= mainCharacter->fallingGravityAmount;
		(*movementVector).Z += gravityAccumulation;
	}
}

void StateMC_NonCombatInAir::MoveForward(float Value)
{

	FVector direction = mainCharacter->cameraBoom->GetForwardVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce * mainCharacter->jumpDirectionalMultiplier);
	*movementVector += FVector(direction.X, direction.Y, 0);
	//moveX = Value * mainCharacter->mainCamera->GetForwardVector().X * mainCharacter->accelerationForce;
}

void StateMC_NonCombatInAir::MoveRight(float Value)
{

	//moveY = Value * mainCharacter->accelerationForce;
	FVector direction = mainCharacter->cameraBoom->GetRightVector();
	direction.Z = 0;
	direction.Normalize();
	direction *= (Value * mainCharacter->accelerationForce * mainCharacter->jumpDirectionalMultiplier);
	*movementVector += FVector(direction.X, direction.Y, 0);
}