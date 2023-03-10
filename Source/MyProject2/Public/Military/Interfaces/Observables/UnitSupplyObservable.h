#pragma once
#include "Military/Interfaces/Observers/UnitSupplyObserver.h"

class IUnitSupplyObservable
{
public:
	void NotifyUnitSupply(UUnit* Unit);

	bool AddUnitSupplyObserver(IUnitSupplyObserver* Observer);
	
	bool RemoveUnitSupplyObserver(IUnitSupplyObserver* Observer);
private:
	TArray<IUnitSupplyObserver*> Observers;
};
