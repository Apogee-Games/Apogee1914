
#include "Economics/Interfaces/Observables/StorageObservable.h"

#include "Economics/Instances/StoredGood.h"

void IStorageObservable::NotifyGoodUpdate(EStorageType StorageType, UStoredGood* Good)
{
	for (auto& Observer: Observers)
	{
		Observer->GoodIsUpdated(StorageType, Good);
	}
}

bool IStorageObservable::AddStorageObserver(IStorageObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IStorageObservable::RemoveStorageObserver(IStorageObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
