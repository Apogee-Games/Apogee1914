#pragma once
#include "Engine/DataTable.h"
#include "Terrain.generated.h"

USTRUCT()
struct FTerrain : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed = 1;
};
