#pragma once

#include "MyProject2/Economics/Instances/Public/Storage.h"
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
