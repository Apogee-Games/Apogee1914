
#include "Widgets/Military/Supply/UnitsSupplyListWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Military/Managers/UnitsFactory.h"
#include "Military/Managers/UnitsSupplyController.h"

void UUnitsSupplyListWidget::Init()
{
	Country = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
	GetGameInstance()->GetSubsystem<UUnitsFactory>()->AddUnitCreationObserver(this);
}

void UUnitsSupplyListWidget::UnitIsCreated(UUnit* Unit)
{
	if (Country == Unit->GetCountryOwner())
	{
		UnitsListView->AddItem(Unit);
	}
}

// TODO: Add OnUnitRemove :)
