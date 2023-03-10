#pragma once
#include "Economics/Instances/StoredGood.h"
#include "Economics/Interfaces/Observers/StorageObserver.h"

enum class EStorageType : uint8;

class IStorageObservable
{
public:
	void NotifyGoodUpdate(EStorageType StorageType, UStoredGood* Good);
	
	bool AddStorageObserver(IStorageObserver* Observer);
	
	bool RemoveStorageObserver(IStorageObserver* Observer);
private:
	TArray<IStorageObserver*> Observers;
};
