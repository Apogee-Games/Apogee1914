#pragma once
#include "MyProject2/Maps/Precalculations/ProvincesMap.h"
#include "MyProject2/Maps/Precalculations/Boxes/ProvincesBox.h"

class FFlagBoxUpdater: public FRunnable
{
public:
	FFlagBoxUpdater(const TSharedPtr<FProvincesBox>& Box, const UProvincesMap* ProvincesMap, FColor* FlagsColors, const FColor* CountryFlagColor, const FVector2d& FlagSizeVector);
	
	virtual uint32 Run() override;

private:
	const TSharedPtr<FProvincesBox>& Box;

	const UProvincesMap* ProvincesMap;

	FColor* FlagsColors;

	FVector2d SizeVector;

	const FColor* CountryFlagColor;

	FVector2d FlagSizeVector;

	FVector2d GetRelativePosition(const FVector2d& Position) const;

	FColor GetFlagColor(const FVector2d& RelativePosition) const;
};
