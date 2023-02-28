#include "Unit.h"

#include "MyProject2/Administration/Managers/CountriesManager.h"
#include "MyProject2/Military/Managers/UnitsRenderer.h"

FUnit::FUnit(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UUnitsRenderer* UnitsRenderer): UnitDescription(UnitDescription), Province(Province), UnitsRenderer(UnitsRenderer), CountryOwner(CountryOwner), CountryController(CountryOwner)
{
	for (auto& [GoodName, GoodCount]: UnitDescription->EquipmentRequirements)
	{
		EquipmentNeeds.Add(GoodName, GoodCount);
	}
}

FUnit::FUnit(const FUnitDescription* UnitDescription, UProvince* Province, UCountry* CountryOwner, UCountry* CountryController, UUnitsRenderer* UnitsRenderer): UnitDescription(UnitDescription), Province(Province), UnitsRenderer(UnitsRenderer), CountryOwner(CountryOwner), CountryController(CountryController)
{
	for (auto& [GoodName, GoodCount]: UnitDescription->EquipmentRequirements)
	{
		EquipmentNeeds.Add(GoodName, GoodCount);
	}
}

bool FUnit::CanTransportUnits() const
{
	return UnitDescription->CanTransport;
}

/*
void FUnit::AddTransportedUnit(FUnit* Unit)
{
	if (!CanTransportUnits()) return;
	TransportedUnits.Add(Unit);
}

void FUnit::RemoveTransportedUnit(FUnit* Unit)
{
	if (!CanTransportUnits()) return;
	TransportedUnits.Remove(Unit);
}*/

void FUnit::Move(UProvince* NewProvince)
{
	Province = NewProvince;
}

UProvince* FUnit::GetPosition() const
{
	return Province;
}

int32 FUnit::Estimate(const TArray<TPair<UProvince*, int>>& Path)
{
	//TODO: Add additional logic for better estimation
	int32 Result = 0;
	for (const auto& Pair : Path)
	{
		Result += Pair.Value;
	}
	return Result;
}

UCountry* FUnit::GetCountryOwner() const
{
	return CountryOwner;
}

UCountry* FUnit::GetCountryController() const
{
	return CountryController;
}

const TMap<FName, int32>& FUnit::GetEquipmentNeeds() const
{
	return EquipmentNeeds;
}

int32 FUnit::GetUnitTypeEquipmentRequirement(const FName& GoodName) const
{
	return UnitDescription->EquipmentRequirements[GoodName];
}

void FUnit::SupplyEquipment(const FName& GoodName, int32 Amount)
{
	EquipmentNeeds[GoodName] -= Amount;
}

const FName& FUnit::GetUnitName() const
{
	return UnitDescription->UnitName;
}

