#pragma once
#include "Engine/DataTable.h"
#include "Province.generated.h"

USTRUCT()
struct FProvince : public FTableRowBase
{
	GENERATED_BODY()

	FProvince();

	FProvince(const FColor& Color, const FString& Name, const FString& CountryTag, const int& Population);

	FColor GetColor() const;

	FString GetCountryTag() const;

	FString GetName() const;

	int GetPopulation() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString CountryTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Population;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString TerrainName;
};
