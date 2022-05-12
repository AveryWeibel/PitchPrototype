// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMC_NonCombatInAir.h"
#include "MainCharacter.h"
#include "CustomDefines.h"

DEFINE_LOG_CATEGORY(Log171InAir);

StateMC_NonCombatInAir::StateMC_NonCombatInAir(AMainCharacter* mainCharacter) : State_MainCharacter(mainCharacter)
{
	stateName = TidesStateName::NonCombatInAir;
}

StateMC_NonCombatInAir::~StateMC_NonCombatInAir()
{
}

void StateMC_NonCombatInAir::Start()
{
	UE_LOG(Log171InAir, Log, TEXT("Enter State NonCombatInAir"));
	gravityAccumulation = 0;
	JumpDirMultiplierAlpha = 0;

	//Set Ground Trace Params
	if(mainCharacter)
	{
		groundTraceParams.AddIgnoredActor(mainCharacter);
		//GroundTraceResponseParams.DefaultResponseParam.
	}

	InAirStartHeight = mainCharacter->bodyCollider->GetComponentLocation().Z;
}

void StateMC_NonCombatInAir::Execute(float DeltaTime)
{
	//apply movement inputs for this frame
	JumpDirMultiplierAlpha = FMath::Lerp(1.0f, mainCharacter->jumpDirectionalMultiplier, FMath::Clamp<float>(mainCharacter->jumpDirMultiplierRampSpeed * DeltaTime, mainCharacter->jumpDirectionalMultiplier, 1));
	
	//ApplyGravity();
	//UE_LOG(Log171General, Log, TEXT("MovementVectorInAir: X: %f Y: %f Z: %f"), movementVector->X, movementVector->Y, movementVector->Z);

	//Rotate model towards the movement vector
	RotateCharacterModel(DeltaTime, mainCharacter->horizontalVelocity, mainCharacter->modelTurningRate);
	
	//Move character
	MoveCharacter(DeltaTime,mainCharacter->jumpDirectionalMultiplier,  true, false);

	//Move camera
	MoveCameraUnLocked(DeltaTime);
	
	
}

void StateMC_NonCombatInAir::BeginOverlapFeet(AActor& OtherActor)
{
	print("Hit Feets");

	//Zero out vertical actual velocity and vertical input velocity
	gravityAccumulation = 0;
	JumpDirMultiplierAlpha = 0;
	//movementVector->Z = 0;

	if(!OtherActor.Tags.Contains("Ocean"))
	{
		const float FallDist = FMath::Abs(InAirStartHeight - mainCharacter->bodyCollider->GetComponentLocation().Z);

		if(FallDist > mainCharacter->FallDamageDistThreshold)
		{
			const int DamageDist = FallDist - mainCharacter->FallDamageDistThreshold;
			mainCharacter->takeDamage( (DamageDist / 100) * mainCharacter->DamagePerHundredUnits);
			if(mainCharacter->playerHealth > 0)
			{
				RequestStateChange(TidesStateName::NonCombatMove);
			}
		}
		else
		{
			RequestStateChange(TidesStateName::NonCombatMove);
		}
		
		UE_LOG(Log171InAir, Log, TEXT("Fall height: %f"), FallDist);
	}
}

void StateMC_NonCombatInAir::ApplyGravity(float DeltaTime)
{
	//New comments
	if (VerticalVector > -mainCharacter->maxFallingSpeed)
	{
		gravityAccumulation -= mainCharacter->fallingGravityAmount * DeltaTime;
		VerticalVector += gravityAccumulation * DeltaTime;
	}
}

void StateMC_NonCombatInAir::MoveForward(float Value)
{
	GetForwardInput(Value);
}

void StateMC_NonCombatInAir::MoveRight(float Value)
{
	GetRightInput(Value);
}

void StateMC_NonCombatInAir::TurnRate(float Value)
{
	AddCameraOrbitYaw(Value);
}

void StateMC_NonCombatInAir::EnterWater()
{
	State_MainCharacter::EnterWater();
	RequestStateChange(TidesStateName::InWater);
}

void StateMC_NonCombatInAir::Die()
{
	State_MainCharacter::Die();
	RequestStateChange(TidesStateName::Dead);
}

void StateMC_NonCombatInAir::LookUpRate(float Value)
{
	AddCameraOrbitPitch(Value);
}
