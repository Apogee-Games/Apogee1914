
#include "Maps/Outlines/OutlineMap.h"

#include "MyGameInstance.h"
#include "Administration/Managers/ProvinceManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Maps/Precalculations/Distances/DistancesMap.h"
#include "Utils/TextureUtils.h"

#define UpdateResource UpdateResource

void UOutlineMap::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UOutlineMap::CreateOutline()
{
	const UProvincesMap* ProvincesMap = GetGameInstance()->GetSubsystem<UProvincesMap>();
	const UDistancesMap* DistancesMap = GetGameInstance()->GetSubsystem<UDistancesMap>();
	const UProvinceManager* ProvinceManager = GetGameInstance()->GetSubsystem<UProvinceManager>();
	
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

void UOutlineMap::Clear()
{
	OutlinesMapTexture = nullptr;
}

void UOutlineMap::Init(UScenario* Scenario)
{
	OutlinesMapTexture = Scenario->OutlinesMapTexture;
	SizeVector = FTextureUtils::GetTextureSizeVector(OutlinesMapTexture);
}
