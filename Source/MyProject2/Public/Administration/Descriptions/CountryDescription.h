#pragma once
#include "IdeologyDescription.h"
#include "Engine/DataTable.h"
#include "CountryDescription.generated.h"

USTRUCT(BlueprintType)
struct FCountryDescription: public FTableRowBase
{
	GENERATED_BODY()	

	UPROPERTY()
	FName Tag;

	UPROPERTY()
	FName IdeologyTag;
	
	UPROPERTY()
	TArray<FIdeologyDescription> Ideologies;
};
