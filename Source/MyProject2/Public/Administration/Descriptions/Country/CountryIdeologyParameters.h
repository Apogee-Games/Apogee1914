#pragma once
#include "Engine/DataTable.h"
#include "People/Description/PersonDescription.h"
#include "CountryIdeologyParameters.generated.h"

USTRUCT()
struct FCountryIdeologyParameters: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName Tag;
	
	UPROPERTY(EditDefaultsOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly)
	FColor Color;

	UPROPERTY(EditDefaultsOnly)
	UPersonDescription* RulerId;
};
