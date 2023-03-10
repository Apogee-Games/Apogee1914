#pragma once
#include "Engine/DataTable.h"
#include "CountryDescription.generated.h"

USTRUCT(BlueprintType)
struct FCountryDescription: public FTableRowBase
{
	GENERATED_BODY()	

	UPROPERTY()
	FName CountryName;
	
	UPROPERTY()
	FName Tag;

	UPROPERTY()
	FColor Color;
};
