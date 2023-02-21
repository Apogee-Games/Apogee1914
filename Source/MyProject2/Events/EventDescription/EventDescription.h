#pragma once
#include "EventChoice.h"
#include "EventCondition.h"
#include "EventCountriesConditions.h"
#include "Engine/DataTable.h"
#include "EventDescription.generated.h"

USTRUCT()
struct FEventDescription: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName ImagePath;

	UPROPERTY()
	FText Title;

	UPROPERTY()
	FText Text;

	UPROPERTY()
	bool TriggerOnce;
	
	UPROPERTY()
	FEventCountriesConditions CountriesConditions;

	UPROPERTY()
	TArray<FEventCondition> Conditions;

	UPROPERTY()
	TArray<FEventChoice> Choices;
};
