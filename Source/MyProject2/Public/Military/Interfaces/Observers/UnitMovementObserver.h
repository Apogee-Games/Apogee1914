#pragma once
#include "Military/Instances/Units/Unit.h"

class IUnitMovementObserver
{
public:
	virtual ~IUnitMovementObserver() = default;
	virtual void UnitIsMoved(UUnit* Unit, UProvince* From, UProvince* To) = 0;
};
