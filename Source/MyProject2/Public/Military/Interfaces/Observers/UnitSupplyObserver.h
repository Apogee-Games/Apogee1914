#pragma once
#include "Military/Instances/Units/Unit.h"

class IUnitSupplyObserver
{
public:
	virtual ~IUnitSupplyObserver() = default;
	virtual void UnitIsSupplied(UUnit* Unit) = 0;
};
