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

const TArray<UProvince*>& UProvinceManager::GetAllProvinces() const
{
	return ProvincesArray;
}

void UProvinceManager::UnitMovedIn(UProvince* Province, UUnit* Unit)
{
	if (Province->GetCountryController() != Unit->GetCountryController())
	{
		Province->TakeControl(Unit->GetCountryController());
	}
	// TODO: Add notification
}

void UProvinceManager::InitProvinces(UDataTable* ProvinceDescriptionDataTable, UDataTable* TerrainDescriptionDataTable)
{
	for(const auto& [Key,Value]: ProvinceDescriptionDataTable->GetRowMap()) {
		if(Value == nullptr) continue;
		FProvinceDescription* ProvinceDescription = reinterpret_cast<FProvinceDescription*>(Value);
		UProvince* Province = NewObject<UProvince>(GetWorld()); 
		Province->Init(ProvinceDescription, TerrainDescriptionDataTable, nullptr); 
		ProvinceMap.Add(Key.ToString(), Province);
	}
}
