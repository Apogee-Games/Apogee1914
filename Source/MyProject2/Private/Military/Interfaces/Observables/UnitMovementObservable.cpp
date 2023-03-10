#include "Military/Interfaces/Observables/UnitMovementObservable.h"

void IUnitMovementObservable::NotifyUnitMovement(UUnit* Unit, UProvince* From, UProvince* To)
{
	for (auto& Observer: Observers)
	{
		Observer->UnitIsMoved(Unit, From, To);
	}
}

bool IUnitMovementObservable::AddUnitMovementObserver(IUnitMovementObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IUnitMovementObservable::RemoveUnitMovementObserver(IUnitMovementObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
