#include "Maps/ProvincesBox.h"
#include "Maps/MapsDataGatherer.h"

FProvincesBox::FProvincesBox(UMapsDataGatherer* MapsDataGatherer, UCountry* Country): MapsDataGatherer(MapsDataGatherer), Country(Country)
{
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

bool FProvincesBox::operator==(const FProvincesBox& ProvincesBox) const
{
	return Provinces == ProvincesBox.Provinces;
}

bool FProvincesBox::operator>(const FProvincesBox& ProvincesBox) const
{
	return Provinces.Num() > ProvincesBox.GetProvinces().Num();
}

bool FProvincesBox::operator<(const FProvincesBox& ProvincesBox) const
{
	return Provinces.Num() < ProvincesBox.GetProvinces().Num();
}

FProvincesBox::~FProvincesBox()
{
	Provinces.Empty();
	Country = nullptr;
}

void FProvincesBox::AddProvincePositions(UProvince* Province)
{
	const FVector2d& ProvinceLeftTopCorner = MapsDataGatherer->GetLeftTopCorner(Province);
	const FVector2d& ProvinceRightBottomCorner = MapsDataGatherer->GetRightBottomCorner(Province);
	LeftTopCorner.X = FMath::Min(LeftTopCorner.X, ProvinceLeftTopCorner.X);
	LeftTopCorner.Y = FMath::Min(LeftTopCorner.Y, ProvinceLeftTopCorner.Y);
	RightBottomCorner.X = FMath::Max(RightBottomCorner.X, ProvinceRightBottomCorner.X);
	RightBottomCorner.Y = FMath::Max(RightBottomCorner.Y, ProvinceRightBottomCorner.Y);
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

