// Fill out your copyright notice in the Description page of Project Settings.


#include "TickThisAttack.h"

#include "BehaviorTree/BlackboardComponent.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

struct FTickThisAttackMemory
{
	bool weaponActive;
};

UTickThisAttack::UTickThisAttack()
{
	bNotifyTick = true;
	playerDodgedAttack = false;
}

EBTNodeResult::Type UTickThisAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UE_LOG(Log171General, Log, TEXT("Perform Attack Node"))
	UTidesBTTaskNode::ExecuteTask(OwnerComp, NodeMemory);

	playerDodgedAttack = false;
	player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(owningChar->GetWorld(), 0));

	//FTickThisAttackMemory* TaskMemory = reinterpret_cast<FTickThisAttackMemory*>(NodeMemory);
	
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UTickThisAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FinishLatentTask(OwnerComp ,EBTNodeResult::Aborted);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("WeaponActive", false);
	UE_LOG(Log171General, Log, TEXT("Abort attack ticking task"));
	return EBTNodeResult::Aborted;
}

void UTickThisAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ABaseAIController* AIController = Cast<ABaseAIController>(owningChar->GetController());
	if(OwnerComp.GetBlackboardComponent()->GetValueAsBool("RecieveAnimEnd"))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("RecieveAnimEnd", false);
		
		if (AIController)
		{
			AIController->UpdateState(ExitState, owningChar->Animator);
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("WeaponActive", false);
		FinishLatentTask(OwnerComp ,EBTNodeResult::Succeeded);
	}

	//FTickThisAttackMemory* TaskMemory = reinterpret_cast<FTickThisAttackMemory*>(NodeMemory);

	bool weaponActive = OwnerComp.GetBlackboardComponent()->GetValueAsBool("WeaponActive");
	
	auto hitPlayer = Cast<AMainCharacter>(owningChar->Weapon->overlappedPawn);

	// if(hitPlayer)
	// {
	// 	UE_LOG(Log171GuardAI, Log, TEXT("AI Weapon overlaps player"));
	// }
	
	if(weaponActive && hitPlayer && AIController)
	{
		auto AICharacter = Cast<ABaseAICharacter>(AIController->GetCharacter());
		if (AICharacter) {
			hitPlayer->TakeWeaponHit(AICharacter->GetWeaponDamage());

			//not sure if necessary since finish latent task returns
			/*if (hitPlayer->GetStateMachine()->GetActiveStateName() == TidesStateName::LockedOnDodging) {
				playerDodgedAttack = true;
			}*/
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsBool("WeaponActive", false);
		FinishLatentTask(OwnerComp ,EBTNodeResult::Succeeded);
	}



	//dodge counter
	if (!playerDodgedAttack && 
		owningChar->GetDistanceTo(player) <= 300.0f &&
		player->GetStateMachine()->GetActiveStateName() == TidesStateName::LockedOnDodging) {

		playerDodgedAttack = true;
		player->TakeWeaponHit(0);
	}
}

uint16 UTickThisAttack::GetInstanceMemorySize() const
{
	return sizeof(FTickThisAttackMemory);
}

