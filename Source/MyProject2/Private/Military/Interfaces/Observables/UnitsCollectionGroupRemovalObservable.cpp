#include "Military/Interfaces/Observables/UnitsCollectionGroupRemovalObservable.h"

void IUnitsCollectionGroupRemovalObservable::NotifyUnitsCollectionGroupRemoval(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	for (auto& Observer : Observers)
	{
		Observer->UnitsCollectionGroupIsRemoved(UnitsCollectionGroup);
	}
}

bool IUnitsCollectionGroupRemovalObservable::AddUnitsCollectionGroupRemovalObserver(IUnitsCollectionGroupRemovalObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IUnitsCollectionGroupRemovalObservable::RemoveUnitsCollectionGroupRemovalObserver(IUnitsCollectionGroupRemovalObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}