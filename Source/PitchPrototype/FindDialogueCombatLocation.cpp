// Fill out your copyright notice in the Description page of Project Settings.

#include "FindDialogueCombatLocation.h"
#include "DrawDebugHelpers.h"

UFindDialogueCombatLocation::UFindDialogueCombatLocation() {
	distance = 500.0f;
	radius = 50.0f;
}

EBTNodeResult::Type UFindDialogueCombatLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FVector playerLocation = UGameplayStatics::GetPlayerPawn(owningChar->GetWorld(), 0)->GetActorLocation();

	FVector aiLocation = owningChar->GetActorLocation();

	FVector directionAwayFromPlayer = aiLocation - playerLocation;

	directionAwayFromPlayer.Normalize();

	FVector target = playerLocation + directionAwayFromPlayer*distance;
	
	FCollisionQueryParams queryParams = FCollisionQueryParams::FCollisionQueryParams();
	//queryParams.bDebugQuery = true;
	queryParams.AddIgnoredActor(owningChar);
	queryParams.AddIgnoredActor(UGameplayStatics::GetPlayerPawn(owningChar->GetWorld(), 0));
	bool hitSuccess;
	FHitResult hitResult;
	FColor traceColor = FColor::Red;
	FVector traceCheckVector;
	FVector totalOceanOffset = FVector::FVector(0.0f, 0.0f, 0.0f);
	FVector totalAirOffset = FVector::FVector(0.0f, 0.0f, 0.0f);

	for (float i = -1.0f; i <= 1.0f; ++i) {
		for (float j = -1.0f; j <= 1.0f; ++j) {
			traceCheckVector = (FVector::FVector(i, j, -1.0f)) * 750.0f;
			traceCheckVector += target;
			hitSuccess = owningChar->GetWorld()->LineTraceSingleByChannel(hitResult, target + (FVector::UpVector * distance / 2.0f), traceCheckVector, ECollisionChannel::ECC_Visibility, queryParams);
			if (hitSuccess) {
				if (hitResult.GetActor()->GetName() == "Ocean2_1") {
					traceColor = FColor::Green;
					FVector oceanOffset = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(hitResult.Location, target));
					oceanOffset *= distance/2.0f;
					totalOceanOffset += oceanOffset;
						
					//DrawDebugDirectionalArrow(owningChar->GetWorld(), hitResult.Location, hitResult.Location+oceanOffset, 15.0f, FColor::Purple, false, 3.0f, 0, 5.0f);
				}

				//UE_LOG(Log171General, Log, TEXT("%s"), *hitResult.GetActor()->GetName());
			} else {
				traceColor = FColor::Purple;
				FVector airOffset = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(hitResult.Location, target));
				airOffset *= distance / 2.0f;
				totalAirOffset += airOffset;
			}

			DrawDebugLine(owningChar->GetWorld(), hitResult.TraceStart, hitResult.TraceEnd, traceColor, false, 3.0f, 0, 10.0f);
			traceColor = FColor::Red;
		}
	}

	target += totalOceanOffset;
	target += totalAirOffset;

	DrawDebugDirectionalArrow(owningChar->GetWorld(), playerLocation, target, 15.0f, FColor::Purple, false, 3.0f, 0, 5.0f);

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSys) {
		FNavLocation NavLoc;
		NavSys->GetRandomReachablePointInRadius(target, radius, NavLoc);

		FVector targetLocation = FVector(NavLoc.Location.X, NavLoc.Location.Y, aiLocation.Z);

		DrawDebugLine(owningChar->GetWorld(), playerLocation, target, FColor::Blue, false, 3.0f, 0, 10.0f);

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(targetDest.SelectedKeyName, targetLocation);
		return EBTNodeResult::Succeeded;
	}
	else {
		UE_LOG(Log171General, Log, TEXT("could not find nav sys"));
		return EBTNodeResult::Failed;
	}
}