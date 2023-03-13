#pragma once
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"

class IUnitsCollectionGroupRemovalObserver
{
public:
	virtual ~IUnitsCollectionGroupRemovalObserver() = default;
	virtual void UnitsCollectionGroupIsRemoved(UUnitsCollectionGroup* UnitsCollectionGroup) = 0;
};
