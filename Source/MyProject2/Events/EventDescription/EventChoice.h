#pragma once
#include "EventCondition.h"
#include "EventOutcome.h"
#include "Engine/DataTable.h"
#include "EventChoice.generated.h"

USTRUCT()
struct FEventChoice: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName Name;
	
	UPROPERTY()
	FText Text;
	
	UPROPERTY()
	float AIChance;

	UPROPERTY()
	TArray<FEventOutcome> Outcomes;

	UPROPERTY()
	TArray<FEventCondition> Conditions;
};
