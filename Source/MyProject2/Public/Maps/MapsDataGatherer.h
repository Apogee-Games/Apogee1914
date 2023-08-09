#pragma once

#include "CoreMinimal.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Interfaces/BaseManager.h"
#include "ProvincesBox.h"
#include "MapsDataGatherer.generated.h"

UCLASS()
class MYPROJECT2_API UMapsDataGatherer : public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	FVector2d GetSizeVector() const;

	const FColor& GetColor(int32 Position) const;
	const TArray<FColor>& GetColors() const;

	bool HasProvincePosition(const FColor& Color) const;
	const TArray<int32>& GetProvincePositions(const FColor& Color) const;
	
	const TMap<FColor, TSet<FColor>>& GetNeighbourColors() const;
	const TMap<UProvince*, TSet<UProvince*>>& GetNeighbourProvinces();

	const TArray<TSharedPtr<FProvincesBox>>& GetBoxes() const;

	const FVector2d& GetLeftTopCorner(UProvince* Province) const;
	const FVector2d& GetRightBottomCorner(UProvince* Province) const;

	FORCEINLINE FVector2d GetProvinceCenter(const FColor& Color);
	FORCEINLINE FVector2d GetProvinceCenter(UProvince* Province);
	
	//virtual void ProvinceHasNewControllingCountry(UProvince* Province) override;
	
	virtual ELoadStage GetLoadStage() override;
private:
	UPROPERTY()
	UTexture2D* ProvincesMapTexture;
	TArray<FColor> PositionColor;
	FVector2d SizeVector;
	
	TMap<UProvince*, TSet<UProvince*>> NeighbourProvinces;
	TMap<FColor, TSet<FColor>> NeighbourColors;
	
	TMap<FColor, TArray<int32>> ColorPosition;

	TArray<TSharedPtr<FProvincesBox>> Boxes;
	TMap<UProvince*, TSharedPtr<FProvincesBox>> ProvinceBox;

	TMap<UProvince*, FVector2d> LeftTopCorners;
	TMap<UProvince*, FVector2d> RightBottomCorners;

	TMap<FColor, FVector2d> ProvinceCenters;
	
	void CalculateMappers(UTexture2D* ProvinceMap);
	void FindNeighbours();

	void Clear();
	
	void Init(UScenario* Scenario);
	
	void CalculateProvinceCorners();
	
	void CalculateBoxes();
	void AddProvincesToBox(TSharedPtr<FProvincesBox> Box, UProvince* FromProvince, UCountry* Country, UProvinceManager* ProvinceManager);
	void CreateNewBox(UProvince* Province);
	bool AddProvinceToBox(TSharedPtr<FProvincesBox> Box, UProvince* Province);
	bool MergeBoxesAndAddProvince(TArray<TSharedPtr<FProvincesBox>>& SameCountryBoxes, UProvince* Province);
	void RemoveProvinceFromBox(UProvince* Province);
	bool AddProvinceToNeighbourBoxes(UProvince* Province);

	void CalculateCentersForAllProvinces();
	FVector2d CalculateProvinceCenter(const FColor& Color);
};
