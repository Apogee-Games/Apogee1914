#pragma once
#include "MyProject2/Military/Instances/Unit.h"

class IUnitMovementObserver
{
public:
	virtual ~IUnitMovementObserver() = default;
	virtual void UnitIsMoved(UUnit* Unit, UProvince* From, UProvince* To) = 0;
};
