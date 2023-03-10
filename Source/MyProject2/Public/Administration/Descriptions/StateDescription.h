#pragma once
#include "Engine/DataTable.h"
#include "StateDescription.generated.h"

USTRUCT()
struct FStateDescription : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName StateName;

	UPROPERTY()
	TArray<FName> Provinces;
};
