#pragma once
#include "MyProject2/Economics/Instances/Public/Good.h"
#include "MyProject2/Economics/Interfaces/Observers/StorageObserver.h"

enum class EStorageType : uint8;

class IStorageObservable
{
public:
	void NotifyGoodUpdate(EStorageType StorageType, UGood* Good);
	
	bool AddStorageObserver(IStorageObserver* Observer);
	
	bool RemoveStorageObserver(IStorageObserver* Observer);
private:
	TArray<IStorageObserver*> Observers;
};
