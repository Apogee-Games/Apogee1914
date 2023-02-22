#pragma once
#include "Containers/Map.h"
#include "Engine/DataTable.h"
#include "FactoryDescription.generated.h"

USTRUCT()
struct FFactoryDescription : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY()
	TMap<FName, int32> GoodConsumption; 

	UPROPERTY()
	TMap<FName, int32> ResourceConsumption; // ToDo

	UPROPERTY()
	TMap<FName, int32> GoodOutput;

	UPROPERTY()
	int32 MaxLabours = 0;
};