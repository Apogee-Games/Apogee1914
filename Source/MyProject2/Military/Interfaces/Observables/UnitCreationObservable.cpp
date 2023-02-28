#include "UnitCreationObservable.h"

void IUnitCreationObservable::NotifyUnitCreation(FUnit* Unit)
{
	for (auto& Observer: Observers)
	{
		Observer->UnitIsCreated(Unit);
	}
}

bool IUnitCreationObservable::AddUnitCreationObserver(IUnitCreationObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IUnitCreationObservable::RemoveUnitCreationObserver(IUnitCreationObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
