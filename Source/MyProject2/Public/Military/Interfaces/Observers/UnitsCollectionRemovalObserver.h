#pragma once
#include "Military/Instances/Units/Collections/UnitsCollection.h"

class IUnitsCollectionRemovalObserver
{
public:
	virtual ~IUnitsCollectionRemovalObserver() = default;
	virtual void UnitsCollectionIsRemoved(UUnitsCollection* UnitsCollection) = 0;
};
