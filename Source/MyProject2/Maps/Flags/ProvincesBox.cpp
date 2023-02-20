#include "ProvincesBox.h"

#include "MyProject2/Utils/TextureUtils.h"
#include "MyProject2/Maps/Precalculations/ProvincesMap.h"

FProvincesBox::FProvincesBox(UProvincesMap* ProvincesMap, UCountry* Country): ProvincesMap(ProvincesMap), Country(Country)
{
	SizeVector = ProvincesMap->GetSizeVector();
	ResetCorners();
}

void FProvincesBox::AddProvince(UProvince* Province)
{
	Provinces.Add(Province);
	AddProvincePositions(Province);
}

void FProvincesBox::RemoveProvince(UProvince* Province)
{
	Provinces.Remove(Province);
	RecalculateCorners();
}

FVector2d FProvincesBox::GetLeftTopCorner() const
{
	return LeftTopCorner;
}

FVector2d FProvincesBox::GetRightBottomCorner() const
{
	return RightBottomCorner;
}

UCountry* FProvincesBox::GetCountry() const
{
	return Country;
}

const TArray<UProvince*>& FProvincesBox::GetProvinces() const
{
	return Provinces;
}

void FProvincesBox::AddProvincePositions(UProvince* Province)
{
	for (const auto& Index: ProvincesMap->GetProvincePositions(Province->GetId()))
	{
		const FVector2d Position = FTextureUtils::GetPositionVector(Index, SizeVector);
		LeftTopCorner.X = FMath::Min(LeftTopCorner.X, Position.X);
		LeftTopCorner.Y = FMath::Min(LeftTopCorner.Y, Position.Y);
		RightBottomCorner.X = FMath::Max(RightBottomCorner.X, Position.X);
		RightBottomCorner.Y = FMath::Max(RightBottomCorner.Y, Position.Y);
	}
	//TODO: Add precalculation of top left and bottom right for specific province to avoid recalculation
}

void FProvincesBox::RecalculateCorners()
{
	ResetCorners();
	AddAllProvincesPositions();
}

void FProvincesBox::ResetCorners()
{
	LeftTopCorner = FVector2d(INT_MAX, INT_MAX);
	RightBottomCorner = FVector2d(0, 0);
}

void FProvincesBox::AddAllProvincesPositions()
{
	for (const auto& Province: Provinces)
	{
		AddProvincePositions(Province);
	}
}

