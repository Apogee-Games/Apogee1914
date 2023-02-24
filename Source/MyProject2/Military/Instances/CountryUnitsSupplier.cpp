#include "CountryUnitsSupplier.h"

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

	for (const auto& [GoodName, GoodCount]: Unit->GetEquipmentNeeds())
	{
		if (GoodCount == 0) continue;
		const int GoodProvided = Storage->Demand(GoodName, GoodCount);
		Unit->SupplyEquipment(GoodName, GoodProvided);
	}
}
