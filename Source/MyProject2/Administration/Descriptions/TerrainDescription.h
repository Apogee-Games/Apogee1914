#pragma once
#include "Engine/DataTable.h"
#include "TerrainDescription.generated.h"

USTRUCT()
struct FTerrainDescription : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FString TerrainName;
	
	UPROPERTY()
	float MovementSpeed = 1;
};
