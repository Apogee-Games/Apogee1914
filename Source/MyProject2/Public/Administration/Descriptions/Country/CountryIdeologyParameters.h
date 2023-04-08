#pragma once
#include "Administration/Descriptions/IdeologyDescription.h"
#include "Engine/DataTable.h"
#include "People/Description/PersonDescription.h"
#include "CountryIdeologyParameters.generated.h"

USTRUCT()
struct FCountryIdeologyParameters: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UIdeologyDescription* Ideology;
	
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	FColor Color;

	UPROPERTY(EditDefaultsOnly)
	UPersonDescription* Ruler;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Flag;
};
