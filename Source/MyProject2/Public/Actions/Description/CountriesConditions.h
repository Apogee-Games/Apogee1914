#pragma once
#include "Engine/DataTable.h"
#include "CountriesConditions.generated.h"

USTRUCT()
struct FCountriesConditions : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	bool ForAll;

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> CountriesTags;
};
