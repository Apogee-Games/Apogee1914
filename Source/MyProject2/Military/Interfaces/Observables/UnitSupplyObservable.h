#pragma once
#include "MyProject2/Military/Interfaces/Observers/UnitSupplyObserver.h"

class IUnitSupplyObservable
{
public:
	void NotifyUnitSupply(FUnit* Unit);

	bool AddUnitSupplyObserver(IUnitSupplyObserver* Observer);
	
	bool RemoveUnitSupplyObserver(IUnitSupplyObserver* Observer);
private:
	TArray<IUnitSupplyObserver*> Observers;
};
