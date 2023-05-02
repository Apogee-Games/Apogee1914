#include "Maps/Diplomacy/AllianceMapUpdater.h"


FAllianceMapUpdater::FAllianceMapUpdater(FColor* AlliancesColors, const TArray<int32>& PixelsToUpdate, const UProvince* Province, const FColor NonAlignedCountryColor, const FColor NonAlliedCountryColor)
			:  AlliancesColors(AlliancesColors), PixelsToUpdate(PixelsToUpdate), Province(Province), NonAlignedCountryColor(NonAlignedCountryColor), NonAlliedCountryColor(NonAlliedCountryColor)
{
}

uint32 FAllianceMapUpdater::Run()
{
	for (int32 i : PixelsToUpdate)
	{
		const FColor& Color = GetColor();
		
		AlliancesColors[i] = Color;
	}
	return 0;
}

FColor FAllianceMapUpdater::GetColor() const
{
	const UCountry* Country = Province->GetCountryController();
	if (Country->IsNonAligned()) return NonAlignedCountryColor;
	if (!Country->IsInAlliance()) return NonAlliedCountryColor;
	return Country->GetAlliance()->GetColor();
}
