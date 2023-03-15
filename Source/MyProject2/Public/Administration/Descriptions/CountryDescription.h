#pragma once
#include "FractionDescription.h"
#include "Engine/DataTable.h"
#include "CountryDescription.generated.h"

USTRUCT(BlueprintType)
struct FCountryDescription: public FTableRowBase
{
	GENERATED_BODY()	

	UPROPERTY()
	FName Tag;

	UPROPERTY()
	FName RulingFractionTag;
	
	UPROPERTY()
	TArray<FFractionDescription> Fractions;
};
