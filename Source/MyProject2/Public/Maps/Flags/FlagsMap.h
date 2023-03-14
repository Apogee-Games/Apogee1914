#pragma once
#include "Maps/Precalculations/Boxes/BoxesMap.h"
#include "FlagsMap.generated.h"

UCLASS()
class UFlagsMap: public UWorldSubsystem, public IBoxObserver
{
public:
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void UpdateAllBoxes();
	
	void UpdateBoxes(const TArray<TSharedPtr<FProvincesBox>>& Boxes);

	virtual void BoxWasUpdated(const TSharedPtr<FProvincesBox>& Box) override;
private:
	UPROPERTY()
	UTexture2D* FlagsMapTexture;

	FVector2D SizeVector;

	TMap<UCountry*, const FColor*> CountriesFlagColors;

	TMap<UCountry*, int32> CountriesFlagColorsCount;
	
	FRunnableThread* UpdateBox(const TSharedPtr<FProvincesBox>& Box, FColor* FlagsColors, const FColor* CountryFlagColor, const FVector2d& CountryFlagColorSizeVector);

	const FColor* GetCountryFlagColors(UCountry* Country);

	void UnlockAllCountriesFlagColors();
};