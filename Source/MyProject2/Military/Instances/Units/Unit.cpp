#include "Unit.h"

#include "MyProject2/Administration/Managers/CountriesManager.h"

void UUnit::Init(const FUnitDescription* ProvidedUnitDescription, UProvince* ProvidedProvince, UCountry* ProvidedCountryOwner)
{
	Init(ProvidedUnitDescription, ProvidedProvince, ProvidedCountryOwner, ProvidedCountryOwner);
}

void UUnit::Init(const FUnitDescription* ProvidedUnitDescription, UProvince* ProvidedProvince, UCountry* ProvidedCountryOwner, UCountry* ProvidedCountryController)
{
	UnitDescription = ProvidedUnitDescription;
	Province = ProvidedProvince;
	CountryOwner = ProvidedCountryOwner;
	CountryController = ProvidedCountryController;
	for (auto& [GoodName, GoodCount]: ProvidedUnitDescription->EquipmentRequirements)
	{
		EquipmentNeeds.Add(GoodName, GoodCount);
	}
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
	Province = NewProvince;
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

UCountry* UUnit::GetCountryOwner() const
{
	return CountryOwner;
}

UCountry* UUnit::GetCountryController() const
{
	return CountryController;
}

const TMap<FName, int32>& UUnit::GetEquipmentNeeds() const
{
	return EquipmentNeeds;
}

int32 UUnit::GetUnitTypeEquipmentRequirement(const FName& GoodName) const
{
	return UnitDescription->EquipmentRequirements[GoodName];
}

void UUnit::SupplyEquipment(const FName& GoodName, int32 Amount)
{
	EquipmentNeeds[GoodName] -= Amount;
}

const FName& UUnit::GetUnitName() const
{
	return UnitDescription->UnitName;
}

EMilitaryBranch UUnit::GetMilitaryBranch() const
{
	return EMilitaryBranch::Army;
}

