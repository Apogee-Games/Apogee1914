#include "CountryUnitsSupplier.h"

#include "MyProject2/Military/Managers/UnitsSupplyController.h"

void UCountryUnitsSupplier::Init(UStorage* ProvidedStorage)
{
	Storage = ProvidedStorage;
}

void UCountryUnitsSupplier::Supply()
{
	for (const auto& Unit: Units)
	{
		Supply(Unit);
	}
}

void UCountryUnitsSupplier::AddUnit(UUnit* Unit)
{
	Units.Add(Unit);
}

void UCountryUnitsSupplier::Supply(UUnit* Unit)
{
	// TODO: Add manpower supply
	// TODO: Add system to tune this by a player

	bool IsUnitUpdated = false;
	
	for (const auto& [GoodName, GoodCount]: Unit->GetEquipmentNeeds())
	{
		if (GoodCount == 0) continue;
		const int GoodProvided = Storage->Demand(GoodName, GoodCount);
		IsUnitUpdated |= (GoodProvided != 0);
		Unit->SupplyEquipment(GoodName, GoodProvided);
	}

	if (IsUnitUpdated)
	{
		GetWorld()->GetSubsystem<UUnitsSupplyController>()->NotifyUnitSupply(Unit);
	}
}
