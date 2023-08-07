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

void UUnitsSupplyController::Supply()
{
	for (auto& [Country, Supplier]: CountrySupplier)
	{
		Supplier->Supply();
	}
}

ELoadStage UUnitsSupplyController::GetLoadStage()
{
	return ELoadStage::UnitsSupplyController;
}

void UUnitsSupplyController::Clear()
{
	for (const auto& [Country, Supplier]: CountrySupplier)
	{
		Supplier->MarkAsGarbage();
	}
	CountrySupplier.Empty();
	
	GetGameInstance()->GetSubsystem<UUnitsFactory>()->OnUnitStatusChanged.RemoveAll(this);
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

	GameInstance->GetSubsystem<UUnitsFactory>()->OnUnitStatusChanged.AddUObject(this, &ThisClass::OnUnitStatusChanged);
	GameInstance->GetSubsystem<UInGameTime>()->RegisterListener(this, &UUnitsSupplyController::Supply, SupplyTimeDelta);
}

void UUnitsSupplyController::OnUnitStatusChanged(UUnit* Unit, EUnitStatus UnitStatus)
{
	if (UnitStatus == EUnitStatus::Formed)
	{
		CountrySupplier[Unit->GetCountryController()]->AddUnit(Unit);
	}
	if (UnitStatus == EUnitStatus::Dissolved)
	{
		CountrySupplier[Unit->GetCountryController()]->RemoveUnit(Unit);
	}
}
