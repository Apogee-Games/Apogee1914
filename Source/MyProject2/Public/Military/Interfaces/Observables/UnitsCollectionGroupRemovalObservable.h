#pragma once
#include "Military/Interfaces/Observers/UnitsCollectionGroupRemovalObserver.h"
class IUnitsCollectionGroupRemovalObservable
{
public:
	void NotifyUnitsCollectionGroupRemoval(UUnitsCollectionGroup* UnitsCollectionGroup);
	
	bool AddUnitsCollectionGroupRemovalObserver(IUnitsCollectionGroupRemovalObserver* Observer);
	
	bool RemoveUnitsCollectionGroupRemovalObserver(IUnitsCollectionGroupRemovalObserver* Observer);
private:
	TArray<IUnitsCollectionGroupRemovalObserver*> Observers;
};
