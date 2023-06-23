#pragma once
#include "Maps/Precalculations/Boxes/BoxesMap.h"
#include "FlagsMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UFlagsMap: public UBaseManager, public IBoxObserver
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void Tick();

	virtual void SetScenario(UScenario* Scenario) override;
	
	void UpdateAllBoxes();
	
	void UpdateBoxes(const TArray<TSharedPtr<FProvincesBox>>& Boxes);

	virtual void BoxWasUpdated(const TSharedPtr<FProvincesBox>& Box) override;

	virtual ELoadStage GetLoadStage() override;
private:
	bool IsUpdated = true;
	
	UPROPERTY()
	UTexture2D* FlagsMapTexture;

	FVector2D SizeVector;

	TMap<UCountry*, const FColor*> CountriesFlagColors;

	TMap<UCountry*, int32> CountriesFlagColorsCount;
	
	FRunnableThread* UpdateBox(const TSharedPtr<FProvincesBox>& Box, FColor* FlagsColors, const FColor* CountryFlagColor, const FVector2d& CountryFlagColorSizeVector);

	const FColor* GetCountryFlagColors(UCountry* Country);

	void UnlockAllCountriesFlagColors();

	void Clear();

	void Init(UScenario* Scenario);
};
