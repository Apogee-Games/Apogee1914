#pragma once
#include "Engine/DataTable.h"
#include "CountryIdeologyParameters.generated.h"

USTRUCT()
struct FCountryIdeologyParameters: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName IdeologyTag;
	
	UPROPERTY(EditDefaultsOnly)
	FName CountryName;

	UPROPERTY(EditDefaultsOnly)
	FColor CountryColor;

	UPROPERTY(EditDefaultsOnly)
	FName RulerId;
};
