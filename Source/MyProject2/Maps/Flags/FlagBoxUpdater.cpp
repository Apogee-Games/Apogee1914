#include "FlagBoxUpdater.h"

#include "MyProject2/Maps/Precalculations/ProvincesMap.h"
#include "MyProject2/Utils/TextureUtils.h"

FFlagBoxUpdater::FFlagBoxUpdater(const TSharedPtr<FProvincesBox>& Box, const UProvincesMap* ProvincesMap, FColor* FlagsColors , const FColor* CountryFlagColor, const FVector2d& FlagSizeVector): Box(Box), ProvincesMap(ProvincesMap), FlagsColors(FlagsColors), CountryFlagColor(CountryFlagColor), FlagSizeVector(FlagSizeVector)
{
	SizeVector = ProvincesMap->GetSizeVector();
}

uint32 FFlagBoxUpdater::Run()
{
	for (const auto& Province: Box->GetProvinces())
	{
		for (const auto& i : ProvincesMap->GetProvincePositions(Province->GetId()))
		{
			const FVector2d Position = FTextureUtils::GetPositionVector(i, SizeVector);

			FVector2d RelativePosition = GetRelativePosition(Position);

			FlagsColors[i] = GetFlagColor(RelativePosition);
		}
	}

	return 0;
}

FVector2d FFlagBoxUpdater::GetRelativePosition(const FVector2d& Position) const
{
	return (Position - Box->GetLeftTopCorner()) / (Box->GetRightBottomCorner() - Box->GetLeftTopCorner());
}


FColor FFlagBoxUpdater::GetFlagColor(const FVector2d& RelativePosition) const
{
	const FVector2d FlagPosition = RelativePosition * FlagSizeVector;

	const int Position = FTextureUtils::GetPixelPosition(FlagPosition, FlagSizeVector);

	return CountryFlagColor[Position];
}
