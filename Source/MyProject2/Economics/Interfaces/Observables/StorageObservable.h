#pragma once
#include "MyProject2/Economics/Interfaces/Observers/StorageObserver.h"

enum class EStorageType : uint8;

class IStorageObservable
{
public:
	void NotifyGoodUpdate(EStorageType StorageType, const FName& GoodName, int NewAmount);
	
	bool AddStorageObserver(IStorageObserver* Observer);
	
	bool RemoveStorageObserver(IStorageObserver* Observer);
private:
	TArray<IStorageObserver*> Observers;
};
