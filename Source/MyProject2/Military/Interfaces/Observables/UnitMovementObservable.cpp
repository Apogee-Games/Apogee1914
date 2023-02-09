#include "UnitMovementObservable.h"

void IUnitMovementObservable::NotifyUnitMovement(UUnit* Unit, const FColor& From, const FColor& To)
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
