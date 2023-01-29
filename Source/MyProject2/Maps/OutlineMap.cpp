#include "OutlineMap.h"

#include "MyProject2/Administration/Managers/ProvinceManager.h"
#include "MyProject2/Utils/TextureUtils.h"


void UOutlineMap::CreateOutline()
{
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	
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
			ProvinceManager->AreProvincesNotInTheSameState(ProvincesColor[i], ProvincesColor[i - 1]))
		{
			OutlineColors[i] = OutlineColor;
			continue;
		}
		if (x + 1 < Width && ProvincesColor[i] != ProvincesColor[i + 1] &&
			ProvinceManager->AreProvincesNotInTheSameState(ProvincesColor[i], ProvincesColor[i + 1]))
		{
			OutlineColors[i] = OutlineColor;
			continue;
		}
		if (y > 0 && ProvincesColor[i] != ProvincesColor[i - Width] &&
			ProvinceManager->AreProvincesNotInTheSameState(ProvincesColor[i], ProvincesColor[i - Width]))
		{
			OutlineColors[i] = OutlineColor;
			continue;
		}
		if (y + 1 < Height && ProvincesColor[i] != ProvincesColor[i + Width] &&
			ProvinceManager->AreProvincesNotInTheSameState(ProvincesColor[i], ProvincesColor[i + Width]))
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

void UOutlineMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	OutlinesMapTexture = FTextureUtils::LoadTexture("/Game/maps/outlines");
	ProvincesMapTexture = FTextureUtils::LoadTexture("/Game/maps/provinces");
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}
