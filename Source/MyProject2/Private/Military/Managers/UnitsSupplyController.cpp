#include "Military/Managers/UnitsSupplyController.h"

#include "InGameTime.h"
#include "Administration/Managers/CountriesManager.h"
#include "LevelsOverides/Game/GameLevelGameState.h"
#include "Military/Managers/UnitsFactory.h"


bool UUnitsSupplyController::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && Outer->GetName() == TEXT("Game");
}

void UUnitsSupplyController::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	for (auto& [CountryTag, Country]: GetWorld()->GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountryMap())
	{
		UCountryUnitsSupplier* Supplier = NewObject<UCountryUnitsSupplier>(this);
		Supplier->Init(Country->GetStorage());
		CountrySupplier.Add(Country, Supplier);
	}

	GetWorld()->GetSubsystem<UUnitsFactory>()->AddUnitCreationObserver(this);
	GetWorld()->GetSubsystem<UInGameTime>()->RegisterListener(this, &UUnitsSupplyController::Supply, SupplyTimeDelta);
}

void UUnitsSupplyController::UnitIsCreated(UUnit* Unit)
{
	CountrySupplier[Unit->GetCountryController()]->AddUnit(Unit);
}

void UUnitsSupplyController::Supply()
{
	for (auto& [Country, Supplier]: CountrySupplier)
	{
		Supplier->Supply();
	}
}
