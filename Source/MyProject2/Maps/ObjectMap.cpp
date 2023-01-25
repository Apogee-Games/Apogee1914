#include "ObjectMap.h"

#include "MyProject2/Utils/TextureUtils.h"

TMap<FColor, int> UObjectMap::CalculateProvincesCenters() const
{
	TMap<FColor, unsigned long long> Counts;
	TMap<FColor, FVector2d> Sums;

	const FColor* Colors = FTextureUtils::GetPixels(ProvincesMapTexture, LOCK_READ_ONLY);

	const int Size = SizeVector.X * SizeVector.Y;

	for (unsigned long long i = 0; i < Size; ++i)
	{
		if (!Counts.Contains(Colors[i])) Counts.Add(Colors[i], 0);
		if (!Sums.Contains(Colors[i])) Sums.Add(Colors[i], FVector2d(0, 0));
		Counts[Colors[i]]++;
		Sums[Colors[i]] += FTextureUtils::GetPositionVector(i, SizeVector);
	}

	TMap<FColor, int> Centers;

	for (const auto& SumPair : Counts)
	{
		const FVector2d Center = Sums[SumPair.Key] / Counts[SumPair.Key];
		Centers.Add(SumPair.Key, FTextureUtils::GetPixelPosition(Center, SizeVector));
	}

	FTextureUtils::UnlockPixels(ProvincesMapTexture);

	return Centers;
}

void UObjectMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ProvincesMapTexture = FTextureUtils::LoadTexture("/Game/maps/provinces");
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}