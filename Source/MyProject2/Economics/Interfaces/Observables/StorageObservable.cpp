#include "StorageObservable.h"

#include "MyProject2/Economics/Instances/Public/StoredGood.h"

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
