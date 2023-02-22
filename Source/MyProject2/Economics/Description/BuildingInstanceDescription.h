#pragma once
#include "Engine/DataTable.h"
#include "BuildingInstanceDescription.generated.h"

USTRUCT()
struct FBuildingInstanceDescription : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY()
	FName Type; 

	UPROPERTY()
	int32 Labours;
};
