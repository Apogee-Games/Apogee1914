#include "Military/Interfaces/Observables/UnitsCollectionRemovalObservable.h"

void IUnitsCollectionRemovalObservable::NotifyUnitsCollectionRemoval(UUnitsCollection* UnitsCollection)
{
	for (auto& Observer : Observers)
	{
		Observer->UnitsCollectionIsRemoved(UnitsCollection);
	}
}

bool IUnitsCollectionRemovalObservable::AddUnitsCollectionRemovalObserver(IUnitsCollectionRemovalObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IUnitsCollectionRemovalObservable::RemoveUnitsCollectionRemovalObserver(IUnitsCollectionRemovalObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
