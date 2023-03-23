#pragma once
#include "FractionDescription.h"
#include "Engine/DataTable.h"
#include "ParliamentDescription.generated.h"

USTRUCT()
struct FParliamentDescription: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FFractionDescription> Fractions;
};
