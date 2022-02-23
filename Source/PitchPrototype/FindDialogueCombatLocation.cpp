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

	FVector target = aiLocation + (UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(aiLocation, playerLocation)) * distance * -1);

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSys) {
		FNavLocation NavLoc;
		NavSys->GetRandomReachablePointInRadius(target, radius, NavLoc);

		FVector targetLocation = FVector(NavLoc.Location.X, NavLoc.Location.Y, aiLocation.Z);

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(targetDest.SelectedKeyName, targetLocation);
		return EBTNodeResult::Succeeded;
	}
	else {
		UE_LOG(Log171General, Log, TEXT("could not find nav sys"));
		return EBTNodeResult::Failed;
	}
}