#pragma once
#include "Engine/DataTable.h"
#include "StateDescription.generated.h"

USTRUCT()
struct FStateDescription : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FString StateName;

	UPROPERTY()
	TArray<FString> Provinces;
};
