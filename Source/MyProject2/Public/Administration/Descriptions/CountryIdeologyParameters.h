#pragma once
#include "Engine/DataTable.h"
#include "CountryIdeologyParameter.generated.h"

USTRUCT()
struct FCountryIdeologyParameter: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName IdeologyTag;
	
	UPROPERTY()
	FName IdeologyName;

	UPROPERTY()
	FName CountryName;

	UPROPERTY()
	FColor CountryColor;

	UPROPERTY()
	FName RulerId;
};
