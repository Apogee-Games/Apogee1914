#include "Economics/Interfaces/Observables/BuildingCreationObservable.h"

void IBuildingCreationObservable::NotifyBuildingCreation(UBuilding* Building)
{
	for (auto& Observer: Observers)
	{
		Observer->BuildingIsCreated(Building);
	}
}

bool IBuildingCreationObservable::AddBuildingCreationObserver(IBuildingCreationObserver* Observer)
{
	if (Observers.Contains(Observer)) return false;
	Observers.Add(Observer);
	return true;
}

bool IBuildingCreationObservable::RemoveBuildingCreationObserver(IBuildingCreationObserver* Observer)
{
	if (!Observers.Contains(Observer)) return false;
	Observers.Remove(Observer);
	return true;
}
