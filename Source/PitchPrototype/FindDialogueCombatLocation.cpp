// Fill out your copyright notice in the Description page of Project Settings.


#include "FindDialogueCombatLocation.h"

UFindDialogueCombatLocation::UFindDialogueCombatLocation() {
	distance = 100.0f;
	radius = 50.0f;
}

EBTNodeResult::Type UFindDialogueCombatLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FVector playerLocation = UGameplayStatics::GetPlayerPawn(owningChar->GetWorld(), 0)->GetActorLocation();

	FVector aiLocation = owningChar->GetActorLocation();

	FVector direction = aiLocation + (UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(aiLocation, playerLocation)) * distance * -1.0f);

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSys) {
		FNavLocation NavLoc;
		NavSys->GetRandomReachablePointInRadius(direction, radius, NavLoc);

		FVector targetLocation = NavLoc.Location;

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(targetDest.SelectedKeyName, direction);
		return EBTNodeResult::Succeeded;
	}
	else {
		return EBTNodeResult::Failed;
	}
}