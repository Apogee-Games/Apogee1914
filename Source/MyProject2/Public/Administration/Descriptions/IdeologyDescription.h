#pragma once
#include "Engine/DataTable.h"
#include "IdeologyDescription.generated.h"

USTRUCT()
struct FIdeologyDescription: public FTableRowBase
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
