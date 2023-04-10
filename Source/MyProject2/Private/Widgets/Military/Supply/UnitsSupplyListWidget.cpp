
#include "Widgets/Military/Supply/UnitsSupplyListWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Military/Managers/UnitsFactory.h"
#include "Military/Managers/UnitsSupplyController.h"

void UUnitsSupplyListWidget::Init()
{
	Country = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
	GetGameInstance()->GetSubsystem<UUnitsFactory>()->AddUnitCreationObserver(this);
	GetGameInstance()->GetSubsystem<UUnitsFactory>()->AddUnitRemovalObserver(this);
}

void UUnitsSupplyListWidget::UnitIsCreated(UUnit* Unit)
{
	if (Country == Unit->GetCountryOwner())
	{
		UnitsListView->AddItem(Unit);
	}
}

void UUnitsSupplyListWidget::UnitIsRemoved(UUnit* Unit)
{
	if (Country == Unit->GetCountryOwner())
	{
		UnitsListView->RemoveItem(Unit);
	}
}