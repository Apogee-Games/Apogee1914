#include "Military/Interfaces/Observables/UnitsCollectionGroupCreationObservable.h"


void IUnitsCollectionGroupCreationObservable::NotifyUnitsCollectionGroupCreation(UUnitsCollectionGroup* UnitsCollectionGroup)
{
	for (auto& Observer : Observers)
	{
		Observer->UnitsCollectionGroupIsCreated(UnitsCollectionGroup);
	}
}

bool IUnitsCollectionGroupCreationObservable::AddUnitsCollectionGroupCreationObserver(IUnitsCollectionGroupCreationObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IUnitsCollectionGroupCreationObservable::RemoveUnitsCollectionGroupCreationObserver(IUnitsCollectionGroupCreationObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
