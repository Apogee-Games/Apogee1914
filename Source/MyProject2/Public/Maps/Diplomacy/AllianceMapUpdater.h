#pragma once
#include "Administration/Instances/Province.h"
#include "Administration/Instances/Country.h"
class FAllianceMapUpdater: public FRunnable
{
public:
	
	FAllianceMapUpdater(FColor* AlliancesColors, const TArray<int32>& PixelsToUpdate, const UProvince* Province,FColor NonAlignedCountryColor,FColor NonAlliedCountryColor);
	
	virtual uint32 Run() override;
private:
	FColor NonAlliedCountryColor = FColor(200, 200, 200);
	
	FColor NonAlignedCountryColor;
	
	FColor* AlliancesColors;
	
	const TArray<int32>& PixelsToUpdate;
	
	const UProvince* Province;
	
	FColor GetColor() const;
	
};
