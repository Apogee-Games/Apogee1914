#include "State.h"

#include "MyProject2/Administration/Managers/ProvinceManager.h"

void UState::Init(FStateDescription* StateDescription, const UProvinceManager* ProvinceManager)
{
	Name = StateDescription->StateName;
	
	for (const auto& ProvinceColor: StateDescription->Provinces)
	{
		Provinces.Add(ProvinceManager->GetProvince(ProvinceColor));
	}
}

const FString& UState::GetName() const
{
	return Name;
}

TArray<UProvince*> UState::GetProvinces() const
{
	return Provinces;
}
