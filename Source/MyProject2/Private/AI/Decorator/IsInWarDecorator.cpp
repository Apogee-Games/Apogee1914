// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/IsInWarDecorator.h"

#include "Characters/AIPlayerPawn.h"

bool UIsInWarDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AController* Controller = Cast<AController>(OwnerComp.GetOwner());

	if (!Controller)
	{
		return EBTNodeResult::Failed;
	}

	AAIPlayerPawn* Pawn = Cast<AAIPlayerPawn>(Controller->GetPawn());

	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	return Pawn->GetRuledCountry()->IsInWar();
}
