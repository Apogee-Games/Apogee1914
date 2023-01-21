#pragma once
#include "Engine/DataTable.h"
#include "MyProject2/Economics/Description/FactoryInstanceDescription.h"
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

	FString GetStateId() const;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FFactoryInstanceDescription> Factories; 
	
};
