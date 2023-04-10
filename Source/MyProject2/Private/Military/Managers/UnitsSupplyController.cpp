#include "Military/Managers/UnitsSupplyController.h"

#include "InGameTime.h"
#include "Administration/Managers/CountriesManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Military/Managers/UnitsFactory.h"

void UUnitsSupplyController::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void UUnitsSupplyController::UnitIsCreated(UUnit* Unit)
{
	CountrySupplier[Unit->GetCountryController()]->AddUnit(Unit);
}

void UUnitsSupplyController::UnitIsRemoved(UUnit* Unit)
{
	CountrySupplier[Unit->GetCountryController()]->RemoveUnit(Unit);
}

void UUnitsSupplyController::Supply()
{
	for (auto& [Country, Supplier]: CountrySupplier)
	{
		Supplier->Supply();
	}
}

void UUnitsSupplyController::Clear()
{
	for (const auto& [Country, Supplier]: CountrySupplier)
	{
		Supplier->MarkAsGarbage();
	}
	CountrySupplier.Empty();
	GetGameInstance()->GetSubsystem<UUnitsFactory>()->RemoveUnitCreationObserver(this);
}

void UUnitsSupplyController::Init(UScenario* Scenario)
{
	UGameInstance* GameInstance = GetGameInstance();
	
	for (auto& [CountryTag, Country]: GameInstance->GetSubsystem<UCountriesManager>()->GetCountryMap())
	{
		UCountryUnitsSupplier* Supplier = NewObject<UCountryUnitsSupplier>(this);
		Supplier->Init(Country->GetStorage());
		CountrySupplier.Add(Country, Supplier);
	}

	GameInstance->GetSubsystem<UUnitsFactory>()->AddUnitCreationObserver(this);
	GameInstance->GetSubsystem<UUnitsFactory>()->AddUnitRemovalObserver(this);
	GameInstance->GetSubsystem<UInGameTime>()->RegisterListener(this, &UUnitsSupplyController::Supply, SupplyTimeDelta);
}
