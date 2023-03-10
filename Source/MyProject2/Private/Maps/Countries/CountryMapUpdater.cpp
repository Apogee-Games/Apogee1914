
#include "Maps/Countries/CountryMapUpdater.h"

#include "Utils/TextureUtils.h"

FCountryMapUpdater::FCountryMapUpdater(FColor* CountriesColors, const TArray<int32>& PixelsToUpdate,
                                       const UProvince* Province, const TArray<int32>& Distances, const FVector2d& SizeVector,
                                       int32 CrossLineWidth)
	: CountriesColors(CountriesColors), PixelsToUpdate(PixelsToUpdate), Province(Province), Distances(Distances),
	  SizeVector(SizeVector), CrossLineWidth(CrossLineWidth)
{
}

uint32 FCountryMapUpdater::Run()
{
	for (int32 i : PixelsToUpdate)
	{
		FVector2D Position = FTextureUtils::GetPositionVector(i, SizeVector);

		const FColor& Color = GetColor(Position);

		const int32 Distance = Distances[i];

		CountriesColors[i] = Color.WithAlpha(255 - FMath::Min(10, Distance + 1) * 10);
	}
	return 0;
}

const FColor& FCountryMapUpdater::GetColor(const FVector2D& Position) const
{
	return FMath::Abs<int>(Position.X - Position.Y) % (2 * CrossLineWidth) < CrossLineWidth
		       ? Province->GetCountryController()->GetColor()
		       : Province->GetOwnerCountry()->GetColor();
}
