#pragma once
#include "MyProject2/Military/Interfaces/Observers/UnitRemovalObserver.h"

class IUnitRemovalObservable
{
public:
	void NotifyUnitRemoval(FUnit* Unit);

	bool AddUnitRemovalObserver(IUnitRemovalObserver* Observer);
	
	bool RemoveUnitRemovalObserver(IUnitRemovalObserver* Observer);
private:
	TArray<IUnitRemovalObserver*> Observers;
};
