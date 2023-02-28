#pragma once
#include "MyProject2/Military/Instances/Units/Unit.h"

class IUnitCreationObserver
{
public:
	virtual ~IUnitCreationObserver() = default;
	virtual void UnitIsCreated(FUnit* Unit) = 0;
};
