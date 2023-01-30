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
	FString ProvinceName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString CountryTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString StateId;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Population;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString TerrainName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, int> Resources;
};
