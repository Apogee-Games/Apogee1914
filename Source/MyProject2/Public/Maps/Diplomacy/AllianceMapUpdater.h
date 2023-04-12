#pragma once
#include "Administration/Instances/Province.h"
#include "Administration/Instances/Country.h"
class FAllianceMapUpdater: public FRunnable
{
public:
	
	FAllianceMapUpdater(FColor* AlliancesColors, const TArray<int32>& PixelsToUpdate, const UProvince* Province,FColor NonAlignedCountryColor,FColor NonAlliedCountryColor);
	
	virtual uint32 Run() override;
private:
	UPROPERTY(EditDefaultsOnly)
	FColor NonAlliedCountryColor = FColor(200, 200, 200);

	UPROPERTY(EditDefaultsOnly)
	FColor NonAlignedCountryColor;
	
	FColor* AlliancesColors;
	
	const TArray<int32>& PixelsToUpdate;
	
	const UProvince* Province;
	
	FColor GetColor() const;
	
};
