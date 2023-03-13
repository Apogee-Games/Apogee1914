
#include "Military/Interfaces/Observables/UnitCreationObservable.h"

void IUnitsCreationObservable::NotifyUnitCreation(UUnit* Unit)
{
	for (auto& Observer: Observers)
	{
		Observer->UnitIsCreated(Unit);
	}
}

bool IUnitsCreationObservable::AddUnitCreationObserver(IUnitCreationObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IUnitsCreationObservable::RemoveUnitCreationObserver(IUnitCreationObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
