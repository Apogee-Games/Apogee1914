#include "UnitSupplyObservable.h"

void IUnitSupplyObservable::NotifyUnitSupply(FUnit* Unit)
{
	for (auto& Observer: Observers)
	{
		Observer->UnitIsSupplied(Unit);
	}
}

bool IUnitSupplyObservable::AddUnitSupplyObserver(IUnitSupplyObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IUnitSupplyObservable::RemoveUnitSupplyObserver(IUnitSupplyObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
