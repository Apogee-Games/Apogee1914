#pragma once

#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Interfaces/Observers/UnitsCollectionRemovalObserver.h"

class IUnitsCollectionRemovalObservable
{
public:
	void NotifyUnitsCollectionRemoval(UUnitsCollection* UnitsCollection);
	
	bool AddUnitsCollectionRemovalObserver(IUnitsCollectionRemovalObserver* Observer);
	
	bool RemoveUnitsCollectionRemovalObserver(IUnitsCollectionRemovalObserver* Observer);
private:
	TArray<IUnitsCollectionRemovalObserver*> Observers;
};
