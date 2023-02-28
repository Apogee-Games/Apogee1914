#include "UnitsSupplyController.h"

#include "UnitsFactory.h"
#include "MyProject2/InGameTime.h"
#include "MyProject2/Administration/Managers/CountriesManager.h"



void UUnitsSupplyController::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	for (auto& [CountryTag, Country]: GetWorld()->GetSubsystem<UCountriesManager>()->GetCountryMap())
	{
		FCountryUnitsSupplier Supplier = FCountryUnitsSupplier(this, Country->GetStorage());
		CountrySupplier.Add(Country, Supplier);
	}

	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitCreationObserver(this);
	GetWorld()->GetSubsystem<UInGameTime>()->RegisterListener(this, &UUnitsSupplyController::Supply, FTimespan(1, 0, 0, 0));
}

void UUnitsSupplyController::UnitIsCreated(FUnit* Unit)
{
	CountrySupplier[Unit->GetCountryController()].AddUnit(Unit);
}

void UUnitsSupplyController::Supply()
{
	for (auto& [Country, Supplier]: CountrySupplier)
	{
		Supplier.Supply();
	}
}
