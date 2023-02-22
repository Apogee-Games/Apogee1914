#pragma once
#include "Containers/Map.h"
#include "Engine/DataTable.h"
#include "FactoryDescription.generated.h"

USTRUCT()
struct FFactoryDescription : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();
	
public:
	// [Good ID:Amount]
	UPROPERTY()
	TMap<FName, int32> GoodConsumption{}; 

	// [Resource ID:Amount]
	UPROPERTY()
	TMap<FName, int32> ResourceConsumption; // ToDo

	// [Good ID:Amount]
	UPROPERTY()
	TMap<FName, int32> GoodOutput;

	UPROPERTY()
	int32 MaxLabours{};
};