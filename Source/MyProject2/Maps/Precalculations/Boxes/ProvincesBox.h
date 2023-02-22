#pragma once
#include "MyProject2/Administration/Instances/Country.h"
#include "MyProject2/Administration/Instances/Province.h"
#include "MyProject2/Maps/Precalculations/ProvincesMap.h"

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

	static bool CompareAscending(const TSharedPtr<FProvincesBox>& A, const TSharedPtr<FProvincesBox>& B)
	{
		return A->GetProvinces().Num() < B->GetProvinces().Num();
	}
	
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
