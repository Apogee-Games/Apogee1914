#pragma once
#include "ProvincesBox.h"
#include "MyProject2/Administration/Managers/ProvinceManager.h"
#include "MyProject2/Interfaces/FOnFullInitialization.h"
#include "MyProject2/Maps/Interfaces/Observable/BoxObservable.h"

#include "BoxesMap.generated.h"

UCLASS()
class UBoxesMap: public UWorldSubsystem, public FOnFullInitialization, public IProvinceControllingCountryObserver, public IBoxObservable
{
	GENERATED_BODY()
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void Init();
	
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
};

