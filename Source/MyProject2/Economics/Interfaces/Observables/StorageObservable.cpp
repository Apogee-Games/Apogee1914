#include "StorageObservable.h"

void IStorageObservable::NotifyGoodUpdate(EStorageType StorageType, const FName& GoodName, int NewAmount)
{
	for (auto& Observer: Observers)
	{
		Observer->GoodIsUpdated(StorageType, GoodName, NewAmount);
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
