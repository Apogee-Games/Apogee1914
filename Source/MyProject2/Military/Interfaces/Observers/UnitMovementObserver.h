#pragma once
#include "MyProject2/Military/Instances/Units/Unit.h"

class IUnitMovementObserver
{
public:
	virtual ~IUnitMovementObserver() = default;
	virtual void UnitIsMoved(FUnit* Unit, UProvince* From, UProvince* To) = 0;
};
