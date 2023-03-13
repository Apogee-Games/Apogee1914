#include "Military/Interfaces/Observables/UnitsCollectionCreationObservable.h"

void IUnitsCollectionCreationObservable::NotifyUnitsCollectionCreation(UUnitsCollection* UnitsCollection)
{
	for (auto& Observer : Observers)
	{
		Observer->UnitsCollectionIsCreated(UnitsCollection);
	}
}

bool IUnitsCollectionCreationObservable::AddUnitsCollectionCreationObserver(IUnitsCollectionCreationObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IUnitsCollectionCreationObservable::RemoveUnitsCollectionCreationObserver(IUnitsCollectionCreationObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
