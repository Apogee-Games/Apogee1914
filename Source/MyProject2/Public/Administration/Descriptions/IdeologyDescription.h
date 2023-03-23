#pragma once
#include "Engine/DataTable.h"
#include "IdeologyDescription.generated.h"

USTRUCT()
struct FIdeologyDescription: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName Tag;

	UPROPERTY()
	FText IdeologyName;

	UPROPERTY()
	FColor Color;
};
