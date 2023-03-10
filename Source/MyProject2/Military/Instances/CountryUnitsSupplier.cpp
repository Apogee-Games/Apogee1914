#include "CountryUnitsSupplier.h"

#include "MyProject2/Military/Managers/UnitsSupplyController.h"

FCountryUnitsSupplier::FCountryUnitsSupplier(UUnitsSupplyController* Parent, UStorage* Storage): Parent(Parent), Storage(Storage)
{

}

void FCountryUnitsSupplier::Supply()
{
	for (const auto& Unit: Units)
	{
		Supply(Unit);
	}
}

void FCountryUnitsSupplier::AddUnit(UUnit* Unit)
{
	Units.Add(Unit);
}

void FCountryUnitsSupplier::Supply(UUnit* Unit)
{
	// TODO: Add manpower supply
	// TODO: Add system to tune this by a player

	bool IsUnitUpdated = false;
	
	for (const auto& [GoodName, GoodCount]: Unit->GetSupplyNeeds()->GetNeeds())
	{
		if (GoodCount == 0) continue;
		const int GoodProvided = Storage->Demand(GoodName, GoodCount);
		IsUnitUpdated |= (GoodProvided != 0);
		Unit->GetSupplyNeeds()->SupplyEquipment(GoodName, GoodProvided);
	}

	if (IsUnitUpdated)
	{
		Parent->NotifyUnitSupply(Unit);
	}
}
