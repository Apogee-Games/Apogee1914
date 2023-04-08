#pragma once
#include "FractionDescription.h"
#include "Engine/DataTable.h"
#include "ParliamentDescription.generated.h"

USTRUCT()
struct FParliamentDescription: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FText Name;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FFractionDescription> Fractions;
};
