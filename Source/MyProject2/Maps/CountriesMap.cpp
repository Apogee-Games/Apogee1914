#include "CountriesMap.h"

#include "MyProject2/TextureUtils.h"

FCountriesMap::FCountriesMap(): GameState(nullptr), CountriesMapTexture(nullptr), ProvincesMapTexture(nullptr)
{
}

FCountriesMap::FCountriesMap(AMyGameState* GameState):
	GameState(GameState),
	CountriesMapTexture(GameState->GetCountriesMapTexture()),
	ProvincesMapTexture(GameState->GetProvincesMapTexture())
{
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}

FCountriesMap::FCountriesMap(UTexture2D* CountriesMapTexture, UTexture2D* ProvincesMapTexture, AMyGameState* GameState):
	GameState(GameState), CountriesMapTexture(CountriesMapTexture), ProvincesMapTexture(ProvincesMapTexture)
{
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}

void FCountriesMap::UpdateCountriesMapColors() const
{
	const FColor* ProvincesColors = FTextureUtils::GetPixels(ProvincesMapTexture, LOCK_READ_ONLY);

	FColor* CountriesColors = FTextureUtils::GetPixels(CountriesMapTexture, LOCK_READ_WRITE);

	const int Size = SizeVector.X * SizeVector.Y;

	for (int i = 0; i < Size; ++i)
	{
		CountriesColors[i] = GameState->GetCountryColor(ProvincesColors[i]);
	}

	FTextureUtils::UnlockPixels(CountriesMapTexture);

	FTextureUtils::UnlockPixels(ProvincesMapTexture);

	CountriesMapTexture->UpdateResource();
}
