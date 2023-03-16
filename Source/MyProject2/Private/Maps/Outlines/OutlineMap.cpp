
#include "Maps/Outlines/OutlineMap.h"

#include "MyGameInstance.h"
#include "Administration/Managers/ProvinceManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Maps/Precalculations/Distances/DistancesMap.h"
#include "Utils/TextureUtils.h"

#define UpdateResource UpdateResource

void UOutlineMap::CreateOutline()
{
	const UProvincesMap* ProvincesMap = GetWorld()->GetSubsystem<UProvincesMap>();
	const UDistancesMap* DistancesMap = GetWorld()->GetSubsystem<UDistancesMap>();
	const UProvinceManager* ProvinceManager = GetWorld()->GetSubsystem<UProvinceManager>();
	
	FColor* OutlineColors = FTextureUtils::GetPixels(OutlinesMapTexture, LOCK_READ_WRITE);

	for (const auto& Province: ProvinceManager->GetAllProvinces())
	{
		for (const auto& Position: ProvincesMap->GetProvincePositions(Province->GetId()))
		{
			OutlineColors[Position] = (DistancesMap->GetProvincesDistance(Position) ? OutlineColor : BackgroundColor);
		}
	}

	FTextureUtils::UnlockPixels(OutlinesMapTexture);

	OutlinesMapTexture->UpdateResource();
}

bool UOutlineMap::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UOutlineMap::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	GetWorld()->GetSubsystem<UDistancesMap>()->RegisterOnFullInitializationAction(this, &UOutlineMap::CreateOutline);
	OutlinesMapTexture = GetWorld()->GetGameInstance<UMyGameInstance>()->ActiveScenario->OutlinesMapTexture;
	SizeVector = FTextureUtils::GetTextureSizeVector(OutlinesMapTexture);
}
