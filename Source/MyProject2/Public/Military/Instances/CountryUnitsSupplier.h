#pragma once

#include "Economics/Instances/Storage.h"
#include "Units/Unit.h"

class UUnitsSupplyController;

class FCountryUnitsSupplier
{
public:

	FCountryUnitsSupplier(UUnitsSupplyController* Parent, UStorage* Storage);

	void Supply();

	void AddUnit(UUnit* Unit);
	
private:

	UPROPERTY();
	UUnitsSupplyController* Parent;

	UPROPERTY()
	UStorage* Storage;

	TArray<UUnit*> Units;

	void Supply(UUnit* Unit);
};
