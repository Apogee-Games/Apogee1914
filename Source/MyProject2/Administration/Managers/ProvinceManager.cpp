#include "ProvinceManager.h"

#include "MyProject2/Administration/Descriptions/CountryDescription.h"

void UProvinceManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UDataTable* ProvinceDescriptionDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/provinces_description"));

	UDataTable* TerrainDescriptionDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/terrain_description"));

	InitProvinces(ProvinceDescriptionDataTable, TerrainDescriptionDataTable);

	ProvinceMap.GenerateValueArray(ProvincesArray);
}

UProvince* UProvinceManager::GetProvince(const FColor& ProvinceColor) const
{
	return GetProvince(ProvinceColor.ToHex());
}

UProvince* UProvinceManager::GetProvince(const FString& ProvinceColorHex) const
{
	return ProvinceMap.Contains(ProvinceColorHex) ? ProvinceMap[ProvinceColorHex] : nullptr;
}

TArray<UProvince*> UProvinceManager::GetAllProvinces() const
{
	return ProvincesArray;
}

void UProvinceManager::InitProvinces(UDataTable* ProvinceDescriptionDataTable, UDataTable* TerrainDescriptionDataTable)
{
	for(const auto& [Key,Value]: ProvinceDescriptionDataTable->GetRowMap()) {
		if(Value == nullptr) continue;
		// GetProvinceData
		FProvinceDescription* ProvinceDescription = reinterpret_cast<FProvinceDescription*>(Value);
		UProvince* Province = NewObject<UProvince>(); // Get New Province
		Province->Init(ProvinceDescription, TerrainDescriptionDataTable, nullptr); // Init Province Data
		ProvinceMap.Add(Key.ToString(), Province); // Save Province Data to ProvinceMap<Name, UProvince*>
	}
}