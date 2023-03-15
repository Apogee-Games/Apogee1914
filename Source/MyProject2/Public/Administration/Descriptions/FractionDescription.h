#pragma once
#include "Engine/DataTable.h"
#include "FractionDescription.generated.h"

USTRUCT()
struct FFractionDescription: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName FractionTag;
	
	UPROPERTY()
	FName FractionName;

	UPROPERTY()
	FName CountryName;

	UPROPERTY()
	FColor CountryColor;
};
