#pragma once
#include "Military/Instances/CountryUnitsSupplier.h"
#include "Military/Interfaces/Observables/UnitSupplyObservable.h"
#include "Military/Interfaces/Observers/UnitCreationObserver.h"

#include "UnitsSupplyController.generated.h"


UCLASS()
class UUnitsSupplyController: public UWorldSubsystem, public IUnitCreationObserver, public IUnitSupplyObservable
{
	GENERATED_BODY()
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	virtual void UnitIsCreated(UUnit* Unit) override;

	void Supply();

private:
	TMap<UCountry*, FCountryUnitsSupplier> CountrySupplier;
};
