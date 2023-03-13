#pragma once
#include "Military/Instances/Units/Collections/UnitsCollection.h"

class IUnitsCollectionCreationObserver
{
public:
	virtual ~IUnitsCollectionCreationObserver() = default;
	virtual void UnitsCollectionIsCreated(UUnitsCollection* UnitsCollection) = 0;
};
