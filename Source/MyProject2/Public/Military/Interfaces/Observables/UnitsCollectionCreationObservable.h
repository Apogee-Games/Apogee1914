#pragma once
#include "Military/Instances/Units/Collections/UnitsCollection.h"
#include "Military/Interfaces/Observers/UnitsCollectionCreationObserver.h"

class IUnitsCollectionCreationObservable
{
public:
	void NotifyUnitsCollectionCreation(UUnitsCollection* UnitsCollection);
	
	bool AddUnitsCollectionCreationObserver(IUnitsCollectionCreationObserver* Observer);
	
	bool RemoveUnitsCollectionCreationObserver(IUnitsCollectionCreationObserver* Observer);
private:
	TArray<IUnitsCollectionCreationObserver*> Observers;
};
