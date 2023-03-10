#pragma once
#include "MyProject2/Military/Instances/Units/Unit.h"

class IUnitSupplyObserver
{
public:
	virtual ~IUnitSupplyObserver() = default;
	virtual void UnitIsSupplied(UUnit* Unit) = 0;
};
