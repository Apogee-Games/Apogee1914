#include "OutlineMap.h"

#include "MyProject2/Maps/Precalculations/ProvincesMap.h"
#include "MyProject2/Utils/TextureUtils.h"

#define UpdateResource UpdateResource

void UOutlineMap::CreateOutline()
{
	const UProvincesMap* ProvincesMap = GetWorld()->GetSubsystem<UProvincesMap>();
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	
	FColor* OutlineColors = FTextureUtils::GetPixels(OutlinesMapTexture, LOCK_READ_WRITE);

	for (const auto& Province: ProvinceManager->GetAllProvinces())
	{
		for (const auto& Position: ProvincesMap->GetProvincePositions(Province->GetId()))
		{
			OutlineColors[Position] = (ProvincesMap->GetProvincesDistance(Position) ? OutlineColor : BackgroundColor);
		}
	}

	FTextureUtils::UnlockPixels(OutlinesMapTexture);

	OutlinesMapTexture->UpdateResource();
}

void UOutlineMap::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	OutlinesMapTexture = FTextureUtils::LoadTexture("/Game/maps/outlines");
	SizeVector = FTextureUtils::GetTextureSizeVector(OutlinesMapTexture);
}

void UOutlineMap::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GetWorld()->GetSubsystem<UProvincesMap>()->RegisterOnFullInitializationAction(this, &UOutlineMap::CreateOutline);
}
