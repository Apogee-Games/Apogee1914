#include "Military/Instances/Units/Unit.h"

#include "Administration/Managers/CountriesManager.h"

void UUnit::Init(const FUnitDescription* ProvidedUnitDescription, UProvince* ProvidedProvince)
{
	UnitDescription = ProvidedUnitDescription;
	Province = ProvidedProvince;
	SupplyNeeds = NewObject<UUnitSupplyNeeds>(this);
	SupplyNeeds->Init(ProvidedUnitDescription->EquipmentRequirements);
	Province->AddUnit(this);

}

bool UUnit::CanTransportUnits() const
{
	return UnitDescription->CanTransport;
}

/*
void UUnit::AddTransportedUnit(UUnit* Unit)
{
	if (!CanTransportUnits()) return;
	TransportedUnits.Add(Unit);
}

void UUnit::RemoveTransportedUnit(UUnit* Unit)
{
	if (!CanTransportUnits()) return;
	TransportedUnits.Remove(Unit);
}*/

void UUnit::Move(UProvince* NewProvince)
{
	Province->RemoveUnit(this);
	NewProvince->AddUnit(this);

	Province = NewProvince;
	if (Province->GetCountryController() != CountryController)
	{
		Province->TakeControl(CountryController);
	}
}

UProvince* UUnit::GetPosition() const
{
	return Province;
}

int32 UUnit::Estimate(const TArray<TPair<UProvince*, int>>& Path)
{
	//TODO: Add additional logic for better estimation
	int32 Result = 0;
	for (const auto& Pair : Path)
	{
		Result += Pair.Value;
	}
	return Result;
}

int32 UUnit::GetUnitTypeEquipmentRequirement(const FName& GoodName) const
{
	return UnitDescription->EquipmentRequirements[GoodName];
}

UUnitSupplyNeeds* UUnit::GetSupplyNeeds() const
{
	return SupplyNeeds;
}

const FName& UUnit::GetUnitName() const
{
	return UnitDescription->UnitName;
}

EMilitaryBranch UUnit::GetMilitaryBranch() const
{
	return EMilitaryBranch::Army;
}

void UUnit::SetUnitsCollection(UUnitsCollection* ProvidedUnitsCollection)
{
	 UnitsCollection = ProvidedUnitsCollection;
}

UUnitsCollection* UUnit::GetUnitsCollection() const
{
	return UnitsCollection;
}

