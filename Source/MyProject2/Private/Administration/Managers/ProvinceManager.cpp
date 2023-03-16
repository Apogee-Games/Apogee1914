
#include "Administration/Managers/ProvinceManager.h"

#include "Military/Instances/Units/Unit.h"


void UProvinceManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UDataTable* ProvinceDescriptionDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/provinces_description"));

	UDataTable* TerrainDescriptionDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/terrain_description"));
	
	UDataTable* ResourcesDescriptionDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/resources_description"));

	InitProvinces(ProvinceDescriptionDataTable, TerrainDescriptionDataTable, ResourcesDescriptionDataTable);

	ProvinceMap.GenerateValueArray(ProvincesArray);
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

void UProvinceManager::InitProvinces(UDataTable* ProvinceDescriptionDataTable, UDataTable* TerrainDescriptionDataTable, UDataTable* ResourcesDescriptionDataTable)
{
	for(const auto& [Key,Value]: ProvinceDescriptionDataTable->GetRowMap()) {
		if(Value == nullptr) continue;
		FProvinceDescription* ProvinceDescription = reinterpret_cast<FProvinceDescription*>(Value);
		UProvince* Province = NewObject<UProvince>(this); 
		Province->Init(ProvinceDescription, TerrainDescriptionDataTable, nullptr, ResourcesDescriptionDataTable); 
		ProvinceMap.Add(Key, Province);
	}
}
