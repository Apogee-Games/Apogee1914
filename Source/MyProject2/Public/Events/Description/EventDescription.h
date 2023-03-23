#pragma once
#include "EventChoice.h"
#include "Actions/Description/Condition.h"
#include "Actions/Description/CountriesConditions.h"
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
	FCountriesConditions CountriesConditions;

	UPROPERTY()
	TArray<FCondition> Conditions;

	UPROPERTY()
	TArray<FEventChoice> Choices;
};
