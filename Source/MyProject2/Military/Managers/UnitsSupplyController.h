#pragma once
#include "MyProject2/Military/Instances/CountryUnitsSupplier.h"
#include "MyProject2/Military/Interfaces/Observables/UnitSupplyObservable.h"
#include "MyProject2/Military/Interfaces/Observers/UnitCreationObserver.h"

#include "UnitsSupplyController.generated.h"


UCLASS()
class UUnitsSupplyController: public UWorldSubsystem, public IUnitCreationObserver, public IUnitSupplyObservable
{
	GENERATED_BODY()
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	virtual void UnitIsCreated(FUnit* Unit) override;

	void Supply();

private:
	TMap<UCountry*, FCountryUnitsSupplier> CountrySupplier;
};
