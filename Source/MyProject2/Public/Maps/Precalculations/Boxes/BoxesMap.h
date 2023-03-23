#pragma once
#include "ProvincesBox.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Interfaces/FOnFullInitialization.h"
#include "Maps/Interfaces/Observable/BoxObservable.h"

#include "BoxesMap.generated.h"

UCLASS(Abstract, Blueprintable)
class UBoxesMap: public UGameInstanceSubsystem, public IProvinceControllingCountryObserver, public IBoxObservable
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void SetScenario(UScenario* Scenario);
	
	const TArray<TSharedPtr<FProvincesBox>>& GetBoxes() const;

	const FVector2d& GetLeftTopCorner(UProvince* Province) const;
	
	const FVector2d& GetRightBottomCorner(UProvince* Province) const;

	virtual void ProvinceHasNewControllingCountry(UProvince* Province) override;
private:
	FVector2d SizeVector;
	
	TArray<TSharedPtr<FProvincesBox>> Boxes;

	TMap<UProvince*, TSharedPtr<FProvincesBox>> ProvinceBox;

	TMap<UProvince*, FVector2d> LeftTopCorners;
	
	TMap<UProvince*, FVector2d> RightBottomCorners;

	void CalculateProvinceCorners();
	
	void CalculateBoxes();

	void AddProvincesToBox(TSharedPtr<FProvincesBox> Box, UProvince* FromProvince, UCountry* Country, UProvinceManager* ProvinceManager);

	bool AddProvinceToBox(TSharedPtr<FProvincesBox> Box, UProvince* Province);

	bool MergeBoxesAndAddProvince(TArray<TSharedPtr<FProvincesBox>>& SameCountryBoxes, UProvince* Province);
	
	void RemoveProvinceFromBox(UProvince* Province);
	
	bool AddProvinceToNeighbourBoxes(UProvince* Province);

	void CreateNewBox(UProvince* Province);

	void Clear();

	void Init(UScenario* Scenario);
};