#pragma once
#include "ProvincesBox.h"

#include "FlagsMap.generated.h"

UCLASS()
class UFlagsMap: public UWorldSubsystem
{
public:
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void UpdateAllBoxes();
	
	void UpdateBoxes(const TArray<FProvincesBox>& Boxes);

private:
	UPROPERTY()
	UTexture2D* FlagsMapTexture;

	FVector2D SizeVector;

	TMap<UCountry*, const FColor*> CountriesFlagColors;

	TMap<UCountry*, int> CountriesFlagColorsCount;
	
	FRunnableThread* UpdateBox(const FProvincesBox& Box, FColor* FlagsColors, const FColor* CountryFlagColor, const FVector2d& CountryFlagColorSizeVector) const;

	const FColor* GetCountryFlagColors(UCountry* Country);

	void UnlockAllCountriesFlagColors();
};
