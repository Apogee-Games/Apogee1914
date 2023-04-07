#pragma once
#include "Actions/Description/Condition.h"
#include "Actions/Description/Outcome.h"
#include "Engine/DataTable.h"
#include "EventChoice.generated.h"

USTRUCT()
struct FEventChoice: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName Name;
	
	UPROPERTY(EditDefaultsOnly)
	FText Text;
	
	UPROPERTY(EditDefaultsOnly)
	float AIChance;

	UPROPERTY(EditDefaultsOnly)
	TArray<FOutcome> Outcomes;

	UPROPERTY(EditDefaultsOnly)
	TArray<FCondition> Conditions;
};
