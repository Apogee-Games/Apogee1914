
#include "Administration/Managers/ProvinceManager.h"

#include "MyGameInstance.h"
#include "LevelsOverides/Game/GameLevelGameState.h"

void UProvinceManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

UProvince* UProvinceManager::GetProvince(const FColor& ProvinceColor) const
{
	return GetProvince(*ProvinceColor.ToHex());
}

UProvince* UProvinceManager::GetProvince(const FName& ProvinceColorHex) const
{
	return ProvinceMap.Contains(ProvinceColorHex) ? ProvinceMap[ProvinceColorHex] : nullptr;
}

const TArray<UProvince*>& UProvinceManager::GetAllProvinces() const
{
	return ProvincesArray;
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
	UDataTable* ProvinceDescriptionDataTable = Scenario->ProvinceDescriptionDataTable;

	UDataTable* TerrainDescriptionDataTable = Scenario->TerrainDescriptionDataTable;
	
	const TMap<FName, UResourceDescription*>& ResourcesDescriptions = Scenario->ResourcesDescriptions;

	for(const auto& [Key,Value]: ProvinceDescriptionDataTable->GetRowMap()) {
		if(Value == nullptr) continue;
		FProvinceDescription* ProvinceDescription = reinterpret_cast<FProvinceDescription*>(Value);
		UProvince* Province = NewObject<UProvince>(this); 
		Province->Init(ProvinceDescription, TerrainDescriptionDataTable, nullptr, ResourcesDescriptions); 
		ProvinceMap.Add(Key, Province);
	}
	
	ProvinceMap.GenerateValueArray(ProvincesArray);
}
