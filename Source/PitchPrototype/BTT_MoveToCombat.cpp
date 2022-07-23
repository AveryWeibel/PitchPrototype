// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_MoveToCombat.h"

UBTT_MoveToCombat::UBTT_MoveToCombat() {
	speed = 100;
	bNotifyTick = true;
	maxTime = 5;
}

EBTNodeResult::Type UBTT_MoveToCombat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	startTime = owningChar->GetWorld()->GetTimeSeconds();

	targetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(moveTo.SelectedKeyName);

	owningChar->GetCharacterMovement()->StopActiveMovement();
	owningChar->GetCharacterMovement()->StopMovementImmediately();

	UE_LOG(Log171General, Log, TEXT("MoveCombatCalled"));
	return EBTNodeResult::InProgress;
}

void UBTT_MoveToCombat::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const float executingTime = owningChar->GetWorld()->GetTimeSeconds() - startTime;

	FVector aiLocation = owningChar->GetActorLocation();
	FVector direction = targetLocation - aiLocation;
	direction.Normalize();
	direction.Z = 0;
	direction *= speed;

	owningChar->GetCharacterMovement()->AddImpulse(direction, true);

	//UE_LOG(Log171General, Log, TEXT("Velocity moving away from player: %s"), *owningChar->GetCharacterMovement()->Velocity.ToString());

	//UE_LOG(Log171General, Log, TEXT("current location %f %f %f"), aiLocation.X, aiLocation.Y, aiLocation.Z);
	//UE_LOG(Log171General, Log, TEXT("target location %f %f %f"), targetLocation.X, targetLocation.Y, targetLocation.Z);

	//UE_LOG(Log171General, Log, TEXT("distance %f"), FVector::Distance(aiLocation, targetLocation));

	if (FVector::Distance(aiLocation, targetLocation) <= radius){
		owningChar->GetCharacterMovement()->StopActiveMovement();
		owningChar->GetCharacterMovement()->StopMovementImmediately();

		UE_LOG(Log171General, Log, TEXT("reached location of move to combat"));

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	if (executingTime >= maxTime) {
		owningChar->GetCharacterMovement()->StopActiveMovement();
		owningChar->GetCharacterMovement()->StopMovementImmediately();

		UE_LOG(Log171General, Log, TEXT("max time of move to combat"));

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}