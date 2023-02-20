#pragma once
#include "MyProject2/Administration/Instances/Country.h"
#include "MyProject2/Administration/Instances/Province.h"

class UBoxesMap;

class FProvincesBox
{
public:
	explicit FProvincesBox(UBoxesMap* BoxesMap, UCountry* Country);

	void AddProvince(UProvince* Province);

	void RemoveProvince(UProvince* Province);

	FVector2d GetLeftTopCorner() const;
	
	FVector2d GetRightBottomCorner() const;

	UCountry* GetCountry() const;

	const TArray<UProvince*>& GetProvinces() const;

	bool operator==(const FProvincesBox& ProvincesBox) const;

	bool operator>(const FProvincesBox& ProvincesBox) const;

	bool operator<(const FProvincesBox& ProvincesBox) const;

	~FProvincesBox();

private:
	FVector2d SizeVector;

	const UBoxesMap* BoxesMap;
	
	UCountry* Country;

	TArray<UProvince*> Provinces;

	FVector2d LeftTopCorner;
	
	FVector2d RightBottomCorner;

	void AddProvincePositions(UProvince* Province);

	void RecalculateCorners();
	
	void ResetCorners();

	void AddAllProvincesPositions();
};
