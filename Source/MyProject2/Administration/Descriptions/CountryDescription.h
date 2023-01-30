#pragma once
#include "Engine/DataTable.h"
#include "CountryDescription.generated.h"

USTRUCT(BlueprintType)
struct FCountryDescription: public FTableRowBase
{
	GENERATED_BODY()	

	UPROPERTY()
	FString CountryName;
	
	UPROPERTY()
	FString Tag;

	UPROPERTY()
	FColor Color;
};
