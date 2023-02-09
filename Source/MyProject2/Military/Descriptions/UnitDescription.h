#pragma once
#include "Engine/DataTable.h"
#include "UnitDescription.generated.h"

USTRUCT()
struct FUnitDescription: public FTableRowBase
{
	
	GENERATED_BODY()

	UPROPERTY()
	TArray<FString> CanAccessProvincesTypes;

	UPROPERTY()
	bool CanTransport;
	
};