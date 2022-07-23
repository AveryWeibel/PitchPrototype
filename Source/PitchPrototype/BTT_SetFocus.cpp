// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_SetFocus.h"

UBTT_SetFocus::UBTT_SetFocus() {
	focus = true;
}

EBTNodeResult::Type UBTT_SetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseAIController* AIController = Cast<ABaseAIController>(owningChar->GetController());

	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	TidesStateName stateName = StaticCast<TidesStateName>(blackboard->GetValueAsEnum(FName::FName(TEXT("ActiveState"))));

	if (stateName != TidesStateName::AI_NonCombatIdle) {
		blackboard->SetValueAsObject(focusPawn.SelectedKeyName, UGameplayStatics::GetPlayerPawn(owningChar->GetWorld(), 0));
	}

	if (AIController) {
		if (focus) {
			AActor* pawn = Cast<AActor>(blackboard->GetValueAsObject(focusPawn.SelectedKeyName));

			AIController->SetFocus(pawn, EAIFocusPriority::Gameplay);
		} else {
			AIController->ClearFocus(EAIFocusPriority::Gameplay);
		}

		return EBTNodeResult::Succeeded;
	} else {
		return EBTNodeResult::Failed;
	}
}