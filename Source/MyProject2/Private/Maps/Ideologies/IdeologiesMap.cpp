#include "Maps/Ideologies/IdeologiesMap.h"

#include "Administration/Instances/Country.h"
#include "Administration/Instances/Province.h"
#include "Administration/Managers/ProvinceManager.h"
#include "Maps/Precalculations/ProvincesMap.h"
#include "Utils/TextureUtils.h"

void UIdeologiesMap::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UIdeologiesMap::UpdateMap()
{
	const TArray<UProvince*> Provinces = GetGameInstance()->GetSubsystem<UProvinceManager>()->GetAllProvinces();

	UProvincesMap* ProvincesMap = GetGameInstance()->GetSubsystem<UProvincesMap>();

	FColor* Colors = FTextureUtils::GetPixels(IdeologiesMapTexture, LOCK_READ_WRITE);
	
	for (const auto& Province: Provinces)
	{
		FColor Color = Province->GetCountryController()->GetIdeology()->GetColor();
		for (const auto& Position: ProvincesMap->GetProvincePositions(Province->GetId()))
		{
			Colors[Position] = Color;
		}
	}

	FTextureUtils::UnlockPixels(IdeologiesMapTexture);
	IdeologiesMapTexture->UpdateResource();
}

void UIdeologiesMap::Clear()
{
	IdeologiesMapTexture = nullptr;
}

void UIdeologiesMap::Init(UScenario* Scenario)
{
	IdeologiesMapTexture = Scenario->IdeologiesMapTexture;
	UpdateMap();
}
