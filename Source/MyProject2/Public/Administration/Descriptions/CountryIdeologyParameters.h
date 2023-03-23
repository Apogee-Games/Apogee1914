#pragma once
#include "Engine/DataTable.h"
#include "CountryIdeologyParameters.generated.h"

USTRUCT()
struct FCountryIdeologyParameters: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName IdeologyTag;
	
	UPROPERTY()
	FName CountryName;

	UPROPERTY()
	FColor CountryColor;

	UPROPERTY()
	FName RulerId;
};
