#pragma once
#include "Economics/Interfaces/Observers/BuildingCreationObserver.h"

class IBuildingCreationObservable
{
public:
	void NotifyBuildingCreation(UBuilding* Building);
	
	bool AddBuildingCreationObserver(IBuildingCreationObserver* Observer);
	
	bool RemoveBuildingCreationObserver(IBuildingCreationObserver* Observer);
private:
	TArray<IBuildingCreationObserver*> Observers;
};
