#pragma once
#include "Engine/DataTable.h"
#include "ProvinceDescription.generated.h"

USTRUCT()
struct FProvinceDescription : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ProvinceName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName CountryTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName StateId;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Population;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName TerrainName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, int> Resources;
};
