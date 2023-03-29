#pragma once

#include "Economics/Instances/Storage.h"
#include "Units/Unit.h"
#include "CountryUnitsSupplier.generated.h"

class UUnitsSupplyController;

UCLASS()
class UCountryUnitsSupplier: public UObject
{
	GENERATED_BODY()
public:
	void Init(UStorage* ProvidedStorage);

	void Supply();

	void AddUnit(UUnit* Unit);

	void RemoveUnit(UUnit* Unit);
private:
	UPROPERTY()
	UStorage* Storage;

	UPROPERTY()
	TArray<UUnit*> Units;

	void Supply(UUnit* Unit);
};
