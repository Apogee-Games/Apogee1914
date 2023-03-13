#pragma once
#include "Military/Instances/Units/Collections/UnitsCollectionGroup.h"

class IUnitsCollectionGroupCreationObserver
{
public:
	virtual ~IUnitsCollectionGroupCreationObserver() = default;
	virtual void UnitsCollectionGroupIsCreated(UUnitsCollectionGroup* UnitsCollectionGroup) = 0;
};
