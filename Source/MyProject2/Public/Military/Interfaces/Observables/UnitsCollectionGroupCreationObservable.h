#pragma once
#include "Military/Interfaces/Observers/UnitsCollectionGroupCreationObserver.h"

class IUnitsCollectionGroupCreationObservable
{
public:
	void NotifyUnitsCollectionGroupCreation(UUnitsCollectionGroup* UnitsCollection);
	
	bool AddUnitsCollectionGroupCreationObserver(IUnitsCollectionGroupCreationObserver* Observer);
	
	bool RemoveUnitsCollectionGroupCreationObserver(IUnitsCollectionGroupCreationObserver* Observer);
private:
	TArray<IUnitsCollectionGroupCreationObserver*> Observers;
};
