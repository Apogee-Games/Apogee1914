#pragma once
#include "Unit.h"
#include "MyProject2/Economics/Instances/Public/Storage.h"

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

	UPROPERTY()
	TArray<UUnit*> Units;

	void Supply(UUnit* Unit);
};
