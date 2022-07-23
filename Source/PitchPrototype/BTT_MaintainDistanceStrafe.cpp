// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_MaintainDistanceStrafe.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "CollisionQueryParams.h"
#include "GameFramework/CharacterMovementComponent.h"

struct BTT_MaintainDistanceStrafeMemory
{
	float taskStartTime = 5;
	bool rightDirection = true;
};

UBTT_MaintainDistanceStrafe::UBTT_MaintainDistanceStrafe()
{
	bNotifyTick = true;
	bCreateNodeInstance = false;
}

uint16 UBTT_MaintainDistanceStrafe::GetInstanceMemorySize() const
{
	return sizeof(BTT_MaintainDistanceStrafeMemory);
}

EBTNodeResult::Type UBTT_MaintainDistanceStrafe::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Make sure to call super to initialize varibales
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	BTT_MaintainDistanceStrafeMemory* TaskMemory = reinterpret_cast<BTT_MaintainDistanceStrafeMemory*>(NodeMemory);

	TaskMemory->rightDirection = true;
	TaskMemory->taskStartTime = owningChar->GetWorld()->GetTimeSeconds();
	UE_LOG(Log171GuardAI, Log, TEXT("Strafe Execute at %f"), TaskMemory->taskStartTime);//owningChar == NULL ? TEXT("NULL") : TEXT("NOT NULL"));
	
	FCollisionQueryParams queryParams = FCollisionQueryParams::FCollisionQueryParams();
	queryParams.AddIgnoredActor(owningChar);
	queryParams.AddIgnoredActor(UGameplayStatics::GetPlayerPawn(owningChar->GetWorld(), 0));

	FVector right = owningChar->GetActorLocation() + (owningChar->GetActorRightVector() * speed);
	DrawDebugDirectionalArrow(owningChar->GetWorld(), owningChar->GetActorLocation(), right, 15.0f, FColor::Yellow, false, 3.0f, 0, 5.0f);
	FVector down = right + (FVector::DownVector * 300.0f);

	bool hitSuccess;
	FHitResult hitResult;
	hitSuccess = owningChar->GetWorld()->LineTraceSingleByChannel(hitResult, right, down, ECollisionChannel::ECC_Visibility, queryParams);
	
	bool hitRight;
	FHitResult hitRightResult;
	hitRight = owningChar->GetWorld()->LineTraceSingleByChannel(hitRightResult, owningChar->GetActorLocation(), right*10.0f, ECollisionChannel::ECC_Visibility, queryParams);

	bool hitLeft;
	FHitResult hitLeftResult;
	hitLeft = owningChar->GetWorld()->LineTraceSingleByChannel(hitLeftResult, owningChar->GetActorLocation(), right * 10.0f * -1.0f, ECollisionChannel::ECC_Visibility, queryParams);

	if (hitSuccess) {
		if(hitResult.GetActor()->GetName() == "Ocean2") {
			TaskMemory->rightDirection = false;
			DrawDebugDirectionalArrow(owningChar->GetWorld(), right, down, 15.0f, FColor::Green, false, 3.0f, 0, 5.0f);
		}
	}

	if (hitRight)
	{
		TaskMemory->rightDirection = false;
		DrawDebugDirectionalArrow(owningChar->GetWorld(), owningChar->GetActorLocation(), right * 10.0f, 15.0f, FColor::Green, false, 3.0f, 0, 5.0f);
	}
	
	if (hitLeft)
	{
		TaskMemory->rightDirection = true;
		DrawDebugDirectionalArrow(owningChar->GetWorld(), owningChar->GetActorLocation(), right * 10.0f * -1.0f, 15.0f, FColor::Green, false, 3.0f, 0, 5.0f);
	}
	
	return EBTNodeResult::InProgress;
}

void UBTT_MaintainDistanceStrafe::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	BTT_MaintainDistanceStrafeMemory* TaskMemory = reinterpret_cast<BTT_MaintainDistanceStrafeMemory*>(NodeMemory);
	
	const float executingTime = owningChar->GetWorld()->GetTimeSeconds() - TaskMemory->taskStartTime;

	FVector direction = owningChar->GetActorRightVector();
	direction *= speed;

	if (!TaskMemory->rightDirection) {
		direction *= -1;
	}
	
	//owningChar->GetCharacterMovement()->MoveSmooth(direction, DeltaSeconds);
	owningChar->GetCharacterMovement()->AddImpulse(direction, true);

	UE_LOG(Log171General, Log, TEXT("Velocity strafing: %s"), *owningChar->GetCharacterMovement()->Velocity.ToString());
	
	//UE_LOG(Log171GuardAI, Log, TEXT("Strafe Tick for %f"), executingTime);
	//UE_LOG(Log171GuardAI, Log, TEXT("vector %f %f %f"), direction.X, direction.Y, direction.Z);

	if(executingTime >= timeBetweenAttacks)
	{
		if (attack) {
			ABaseAIController* AIController = Cast<ABaseAIController>(owningChar->GetController());

			UE_LOG(LogTemp, Log, TEXT("See Player"))
				if (AIController)
				{
					UE_LOG(LogTemp, Log, TEXT("Valid Controller"))
						AIController->UpdateState(TidesStateName::AI_AttemptAttack, owningChar->Animator);
					//AIController->UpdateState(TidesStateName::AI_NonCombatIdle, Animator);
				}
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		else {
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}
