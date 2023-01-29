#pragma once
#include "Engine/DataTable.h"
#include "TerrainDescription.generated.h"

USTRUCT()
struct FTerrainDescription : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed = 1;
};
