#pragma once
#include "MyProject2/Military/Instances/Unit.h"
#include "MyProject2/Military/Interfaces/Observers/UnitSupplyObserver.h"

class IUnitSupplyObservable
{
public:
	void NotifyUnitSupply(UUnit* Unit);

	bool AddUnitSupplyObserver(IUnitSupplyObserver* Observer);
	
	bool RemoveUnitSupplyObserver(IUnitSupplyObserver* Observer);
private:
	TArray<IUnitSupplyObserver*> Observers;
};
