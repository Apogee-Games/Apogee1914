#pragma once
#include "Actions/Description/Condition.h"
#include "Actions/Description/Outcome.h"
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
	TArray<FOutcome> Outcomes;

	UPROPERTY()
	TArray<FCondition> Conditions;
};
