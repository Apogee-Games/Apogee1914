#pragma once
#include "Military/Interfaces/Observers/UnitMovementObserver.h"

class IUnitMovementObservable
{
public:
	void NotifyUnitMovement(UUnit* Unit, UProvince* From, UProvince* To);

	bool AddUnitMovementObserver(IUnitMovementObserver* Observer);
	
	bool RemoveUnitMovementObserver(IUnitMovementObserver* Observer);
private:
	TArray<IUnitMovementObserver*> Observers;
};
