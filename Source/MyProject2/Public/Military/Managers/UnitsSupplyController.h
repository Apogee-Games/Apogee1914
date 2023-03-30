#pragma once
#include "Military/Instances/CountryUnitsSupplier.h"
#include "Military/Interfaces/Observables/UnitSupplyObservable.h"
#include "Military/Interfaces/Observers/UnitCreationObserver.h"
#include "Military/Interfaces/Observers/UnitRemovalObserver.h"
#include "UnitsSupplyController.generated.h"


UCLASS(Abstract, Blueprintable)
class UUnitsSupplyController: public UWorldSubsystem, public IUnitCreationObserver, public IUnitSupplyObservable, public IUnitRemovalObserver
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FTimespan SupplyTimeDelta = FTimespan(1, 0, 0, 0);

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	virtual void UnitIsCreated(UUnit* Unit) override;

	virtual void UnitIsRemoved(UUnit* Unit) override;

	void Supply();
	
	virtual void Deinitialize() override;
  
private:
	UPROPERTY()
	TMap<UCountry*, UCountryUnitsSupplier*> CountrySupplier;
};
