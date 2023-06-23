
#include "Administration/Managers/ProvinceManager.h"

#include "MyGameInstance.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

void UProvinceManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

UProvince* UProvinceManager::GetProvince(const FColor& Color) const
{
	if (GEngine && !ProvinceMap.Contains(Color))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, Color.ToString());
		return nullptr;
	}
	return ProvinceMap[Color];
}

const TArray<UProvince*>& UProvinceManager::GetAllProvinces() const
{
	return ProvincesArray;
}

ELoadStage UProvinceManager::GetLoadStage()
{
	return ELoadStage::ProvinceManager;
}

void UProvinceManager::Clear()
{
	for (const auto& Province: ProvincesArray)
	{
		Province->MarkAsGarbage();
	}
	ProvinceMap.Empty();
	ProvincesArray.Empty();
}

void UProvinceManager::Init(UScenario* Scenario)
{
	for(const auto& [Country, List]: Scenario->ProvincesDescriptions) {
		for (const auto& Description: List->Provinces)
		{
			UProvince* Province = NewObject<UProvince>(this); 
			Province->Init(Description); 
			ProvinceMap.Add(Description->Color, Province);
		}
	}
	
	ProvinceMap.GenerateValueArray(ProvincesArray);
}
