#pragma once
#include "CountryIdeologyParameters.h"
#include "Engine/DataTable.h"
#include "CountryDescription.generated.h"

USTRUCT()
struct FCountryDescription: public FTableRowBase
{
	GENERATED_BODY()	

	UPROPERTY()
	FName Tag;

	UPROPERTY()
	FName IdeologyTag;
	
	UPROPERTY()
	TArray<FCountryIdeologyParameters> Ideologies;
};
