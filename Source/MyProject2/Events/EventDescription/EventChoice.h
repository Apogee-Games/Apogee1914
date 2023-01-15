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
	FString Name;
	
	UPROPERTY()
	FString Text;

	UPROPERTY()
	TArray<FEventOutcome> Outcomes;

	UPROPERTY()
	TArray<FEventCondition> Conditions;
};
