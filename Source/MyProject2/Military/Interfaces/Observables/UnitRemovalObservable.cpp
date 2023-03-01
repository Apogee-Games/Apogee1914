#include "UnitRemovalObservable.h"

void IUnitRemovalObservable::NotifyUnitRemoval(UUnit* Unit)
{
	for (auto& Observer: Observers)
	{
		Observer->UnitIsRemoved(Unit);
	}
}

bool IUnitRemovalObservable::AddUnitRemovalObserver(IUnitRemovalObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IUnitRemovalObservable::RemoveUnitRemovalObserver(IUnitRemovalObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
