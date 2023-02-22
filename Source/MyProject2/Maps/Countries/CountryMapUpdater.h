#pragma once
#include "MyProject2/Administration/Instances/Province.h"

class FCountryMapUpdater: public FRunnable
{
public:
	FCountryMapUpdater(FColor* CountriesColors, const TArray<int32>& PixelsToUpdate, const UProvince* Province, const TArray<int32>& Distances, const FVector2d& SizeVector, int32 CrossLineWidth);
	
	virtual uint32 Run() override;
private:
	FColor* CountriesColors;
	
	const TArray<int32>& PixelsToUpdate;
	
	const UProvince* Province;

	const TArray<int32>& Distances;

	FVector2d SizeVector;

	int CrossLineWidth;

	const FColor& GetColor(const FVector2D& Position) const;
};
