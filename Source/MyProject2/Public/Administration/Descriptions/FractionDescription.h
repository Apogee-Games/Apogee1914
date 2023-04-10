#pragma once
#include "IdeologyDescription.h"
#include "Engine/DataTable.h"
#include "FractionDescription.generated.h"

USTRUCT()
struct FFractionDescription: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	UIdeologyDescription* Ideology;
	
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	int32 MembersNumber;
};
