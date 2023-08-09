#pragma once
#include "Scenario.h"
#include "Interfaces/BaseManager.h"
#include "Military/Instances/CountryUnitsSupplier.h"
#include "UnitsSupplyController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnitSupplied, UUnit*)

UCLASS(Abstract, Blueprintable)
class UUnitsSupplyController: public UBaseManager
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FTimespan SupplyTimeDelta = FTimespan(1, 0, 0, 0);

	virtual void SetScenario(UScenario* Scenario) override;
	
	void Supply();

	virtual ELoadStage GetLoadStage() override;

	FOnUnitSupplied OnUnitSupplied;
private:
	UPROPERTY()
	TMap<UCountry*, UCountryUnitsSupplier*> CountrySupplier;

	void Clear();

	void Init(UScenario* Scenario);

	UFUNCTION()
	void OnUnitStatusChanged(UUnit* Unit, EUnitStatus UnitStatus);
};
