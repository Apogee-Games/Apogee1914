#include "OutlineMap.h"

#include "MyProject2/TextureUtils.h"

FOutlineMap::FOutlineMap(): GameState(nullptr), OutlinesMapTexture(nullptr), ProvincesMapTexture(nullptr)
{
}

FOutlineMap::FOutlineMap(AMyGameState* GameState):
	GameState(GameState),
	OutlinesMapTexture(GameState->GetOutlinesMapTexture()),
	ProvincesMapTexture(GameState->GetProvincesMapTexture())
{
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}

FOutlineMap::FOutlineMap(UTexture2D* OutlinesMapTexture, UTexture2D* ProvincesMapTexture, AMyGameState* GameState):
	GameState(GameState), OutlinesMapTexture(OutlinesMapTexture), ProvincesMapTexture(ProvincesMapTexture)
{
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}

void FOutlineMap::CreateOutline()
{
	FColor* OutlineColors = FTextureUtils::GetPixels(OutlinesMapTexture, LOCK_READ_WRITE);

	const FColor* ProvincesColor = FTextureUtils::GetPixels(ProvincesMapTexture, LOCK_READ_ONLY);

	const int Size = SizeVector.X * SizeVector.Y;
	const int Width = SizeVector.X;
	const int Height = SizeVector.Y;

	for (int i = 0; i < Size; ++i)
	{
		const int y = i / static_cast<int>(SizeVector.Y);
		const int x = i % static_cast<int>(SizeVector.Y);

		if (x > 0 && ProvincesColor[i] != ProvincesColor[i - 1] &&
			GameState && GameState->AreProvincesNotInTheSameState(ProvincesColor[i], ProvincesColor[i - 1]))
		{
			OutlineColors[i] = OutlineColor;
			continue;
		}
		if (x + 1 < Width && ProvincesColor[i] != ProvincesColor[i + 1] &&
			GameState && GameState->AreProvincesNotInTheSameState(ProvincesColor[i], ProvincesColor[i + 1]))
		{
			OutlineColors[i] = OutlineColor;
			continue;
		}
		if (y > 0 && ProvincesColor[i] != ProvincesColor[i - Width] &&
			GameState && GameState->AreProvincesNotInTheSameState(ProvincesColor[i], ProvincesColor[i - Width]))
		{
			OutlineColors[i] = OutlineColor;
			continue;
		}
		if (y + 1 < Height && ProvincesColor[i] != ProvincesColor[i + Width] &&
			GameState && GameState->AreProvincesNotInTheSameState(ProvincesColor[i], ProvincesColor[i + Width]))
		{
			OutlineColors[i] = OutlineColor;
			continue;
		}
		OutlineColors[i] = BackgroundColor;
	}

	FTextureUtils::UnlockPixels(OutlinesMapTexture);

	FTextureUtils::UnlockPixels(ProvincesMapTexture);

	OutlinesMapTexture->UpdateResource();
}
