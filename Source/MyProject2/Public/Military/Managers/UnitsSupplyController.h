#pragma once
#include "Scenario.h"
#include "Military/Instances/CountryUnitsSupplier.h"
#include "Military/Interfaces/Observables/UnitSupplyObservable.h"
#include "Military/Interfaces/Observers/UnitCreationObserver.h"
#include "Military/Interfaces/Observers/UnitRemovalObserver.h"
#include "UnitsSupplyController.generated.h"


UCLASS(Abstract, Blueprintable)
class UUnitsSupplyController: public UGameInstanceSubsystem, public IUnitCreationObserver, public IUnitSupplyObservable, public IUnitRemovalObserver
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	UPROPERTY(EditDefaultsOnly)
	FTimespan SupplyTimeDelta = FTimespan(1, 0, 0, 0);

	virtual void UnitIsCreated(UUnit* Unit) override;

	virtual void UnitIsRemoved(UUnit* Unit) override;

	void Supply();
private:
	UPROPERTY()
	TMap<UCountry*, UCountryUnitsSupplier*> CountrySupplier;

	void Clear();

	void Init(UScenario* Scenario);
};
