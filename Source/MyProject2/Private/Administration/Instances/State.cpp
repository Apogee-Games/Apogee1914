
#include "Administration/Instances/State.h"

#include "Administration/Managers/ProvinceManager.h"

void UState::Init(UStateDescription* StateDescription)
{
	Name = StateDescription->Name;
	
	const UProvinceManager* ProvinceManager = GetWorld()->GetGameInstance()->GetSubsystem<UProvinceManager>();

	for (const auto& ProvinceDescription: StateDescription->Provinces)
	{
		Provinces.Add(ProvinceManager->GetProvince(ProvinceDescription->Color));
	}
}

const FName& UState::GetName() const
{
	return Name;
}

const TArray<UProvince*>& UState::GetProvinces() const
{
	return Provinces;
}
