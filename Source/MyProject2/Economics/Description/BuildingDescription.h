#pragma once
#include "Containers/Map.h"
#include "Engine/DataTable.h"
#include "BuildingDescription.generated.h"

USTRUCT()
struct FBuildingDescription : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName BuildingName;
	
	UPROPERTY()
	TMap<FName, int32> GoodConsumption; 

	UPROPERTY()
	TMap<FName, int32> ResourceConsumption;

	UPROPERTY()
	TMap<FName, int32> GoodOutput;

	UPROPERTY()
	int32 MaxLabours = 0;
};