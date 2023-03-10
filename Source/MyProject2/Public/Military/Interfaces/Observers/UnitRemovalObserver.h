#pragma once
#include "Military/Instances/Units/Unit.h"

class IUnitRemovalObserver
{
public:
	virtual ~IUnitRemovalObserver() = default;
	virtual void UnitIsRemoved(UUnit* Unit) = 0;
};
