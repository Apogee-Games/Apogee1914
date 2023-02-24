#pragma once
#include "Engine/DataTable.h"
#include "UnitDescription.generated.h"

USTRUCT()
struct FUnitDescription: public FTableRowBase
{
	
	GENERATED_BODY()

	UPROPERTY()
	FName UnitName;
	
	UPROPERTY()
	TArray<FName> CanAccessProvincesTypes;

	UPROPERTY()
	bool CanTransport;

	UPROPERTY()
	TMap<FName, int> EquipmentRequirements;

	UPROPERTY()
	int ManpowerRequirements;
	
};
