// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BaseTask.h"

EBTNodeResult::Type UBaseTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Controller = Cast<AAIPlayerController>(OwnerComp.GetOwner());

	if (!Controller)
	{
		return EBTNodeResult::Failed;
	}

	Pawn = Cast<AAIPlayerPawn>(Controller->GetPawn());

	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	Country = Pawn->GetRuledCountry();

	if (!Country)
	{
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Succeeded;
}
