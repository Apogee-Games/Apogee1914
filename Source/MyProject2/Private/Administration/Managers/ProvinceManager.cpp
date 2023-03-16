
#include "Administration/Managers/ProvinceManager.h"

#include "MyGameInstance.h"
#include "LevelsOverides/Game/GameLevelGameState.h"


bool UProvinceManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UProvinceManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UScenario* Scenario = GetWorld()->GetGameInstance<UMyGameInstance>()->ActiveScenario;
	
	UDataTable* ProvinceDescriptionDataTable = Scenario->ProvinceDescriptionDataTable;

	UDataTable* TerrainDescriptionDataTable = Scenario->TerrainDescriptionDataTable;
	
	UDataTable* ResourcesDescriptionDataTable = Scenario->ResourcesDescriptionDataTable;

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
