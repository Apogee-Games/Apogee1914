#include "ObjectMap.h"

#include "../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/clsocket/src/ActiveSocket.h"
#include "MyProject2/Utils/TextureUtils.h"

void UObjectMap::CalculateProvincesCenters()
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


	for (const auto& [ProvinceColor, Value] : Counts)
	{
		const FVector2d Center = Sums[ProvinceColor] / Counts[ProvinceColor] / SizeVector;
		ProvinceCenters.Add(ProvinceColor.WithAlpha(0), Center);
	}

	FTextureUtils::UnlockPixels(ProvincesMapTexture);
}

void UObjectMap::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	CalculateProvincesCenters();
}

void UObjectMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ProvincesMapTexture = FTextureUtils::LoadTexture("/Game/maps/provinces");
	SizeVector = FTextureUtils::GetTextureSizeVector(ProvincesMapTexture);
}

FVector2d UObjectMap::GetProvinceCenter(const FColor& Color)
{
	return ProvinceCenters[Color];
}
