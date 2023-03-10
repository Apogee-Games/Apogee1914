#pragma once
#include "Military/Instances/Units/Unit.h"

class IUnitCreationObserver
{
public:
	virtual ~IUnitCreationObserver() = default;
	virtual void UnitIsCreated(UUnit* Unit) = 0;
};
