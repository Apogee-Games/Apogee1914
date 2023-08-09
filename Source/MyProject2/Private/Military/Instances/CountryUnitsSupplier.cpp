
#include "Military/Instances/CountryUnitsSupplier.h"

#include "Military/Managers/UnitsSupplyController.h"


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

void UCountryUnitsSupplier::RemoveUnit(UUnit* Unit)
{
	Units.Remove(Unit);
	// TODO: Free used resources :)
}

void UCountryUnitsSupplier::Supply(UUnit* Unit)
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
		UUnitsSupplyController* UnitsSupplyController = Cast<UUnitsSupplyController>(GetOuter());
		UnitsSupplyController->OnUnitSupplied.Broadcast(Unit);
	}
}
