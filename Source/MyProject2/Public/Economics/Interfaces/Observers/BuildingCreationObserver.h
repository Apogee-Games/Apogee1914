#pragma once
#include "Economics/Instances/Buildings/Building.h"


class IBuildingCreationObserver
{
public:
	virtual ~IBuildingCreationObserver() = default;
	virtual void BuildingIsCreated(UBuilding* Building) = 0;
};
