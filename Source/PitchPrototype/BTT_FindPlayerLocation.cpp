// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindPlayerLocation.h"


EBTNodeResult::Type UBTT_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FVector playerLocation = UGameplayStatics::GetPlayerPawn(owningChar->GetWorld(), 0)->GetActorLocation();

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(targetDest.SelectedKeyName, playerLocation);

	return EBTNodeResult::Succeeded;
}
