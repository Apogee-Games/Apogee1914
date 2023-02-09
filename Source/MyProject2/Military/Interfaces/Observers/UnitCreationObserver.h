#pragma once
#include "MyProject2/Military/Instances/Unit.h"

class IUnitCreationObserver
{
public:
	virtual ~IUnitCreationObserver() = default;
	virtual void UnitIsCreated(UUnit* Unit) = 0;
};
