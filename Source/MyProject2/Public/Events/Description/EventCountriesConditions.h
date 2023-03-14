#pragma once
#include "Engine/DataTable.h"
#include "EventCountriesConditions.generated.h"

USTRUCT()
struct FEventCountriesConditions : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	bool ForAll;

	UPROPERTY()
	TArray<FName> CountriesTags;
};
