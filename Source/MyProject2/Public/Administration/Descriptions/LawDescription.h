#pragma once
#include "Actions/Description/Condition.h"
#include "Actions/Description/CountriesConditions.h"
#include "Actions/Description/Outcome.h"
#include "Engine/DataTable.h"
#include "LawDescription.generated.h"

USTRUCT()
struct FLawDescription: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FCondition> Conditions;

	UPROPERTY()
	FCountriesConditions CountriesConditions;
	
	UPROPERTY()
	TArray<FOutcome> Outcomes;

	UPROPERTY()
	FText LawName;

	UPROPERTY()
	FText Description;

	UPROPERTY()
	FName Group;

	UPROPERTY()
	FName Subgroup;
};
