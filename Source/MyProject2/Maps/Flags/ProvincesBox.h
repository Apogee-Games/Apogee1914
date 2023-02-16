#pragma once
#include "MyProject2/Administration/Instances/Country.h"
#include "MyProject2/Administration/Instances/Province.h"

class UProvincesMap;

class FProvincesBox
{
public:
	explicit FProvincesBox(UProvincesMap* ProvincesMap, UCountry* Country);

	void AddProvince(UProvince* Province);

	void RemoveProvince(UProvince* Province);

	FVector2d GetLeftTopCorner() const;
	
	FVector2d GetRightBottomCorner() const;

	UCountry* GetCountry() const;

	const TArray<UProvince*>& GetProvinces() const;
	
private:
	FVector2d SizeVector;

	const UProvincesMap* ProvincesMap;
	
	UCountry* Country;

	TArray<UProvince*> Provinces;

	FVector2d LeftTopCorner;
	
	FVector2d RightBottomCorner;

	void AddProvincePositions(UProvince* Province);

	void RecalculateCorners();
	
	void ResetCorners();

	void AddAllProvincesPositions();
};
