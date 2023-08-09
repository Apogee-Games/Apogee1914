
#include "Widgets/Military/Supply/UnitsSupplyListWidget.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Military/Managers/UnitsFactory.h"
#include "Military/Managers/UnitsSupplyController.h"

void UUnitsSupplyListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();

	UUnitsFactory* UnitsFactory = GetGameInstance()->GetSubsystem<UUnitsFactory>();
	UnitsFactory->OnUnitStatusChanged.AddUObject(this, &ThisClass::OnUnitStatusChanged);

	UnitsListView->ClearListItems();
	for (UUnit* Unit: UnitsFactory->GetUnits())
	{
		if (Unit->GetCountryController() == OwnerCountry)
		{
			UnitsListView->AddItem(Unit);
		}
	}
}

void UUnitsSupplyListWidget::NativeDestruct()
{
	Super::NativeDestruct();
	GetGameInstance()->GetSubsystem<UUnitsFactory>()->OnUnitStatusChanged.RemoveAll(this);
}

void UUnitsSupplyListWidget::OnUnitStatusChanged(UUnit* Unit, EUnitStatus UnitStatus)
{
	if (UnitStatus == EUnitStatus::Formed)
	{
		if (OwnerCountry == Unit->GetCountryOwner())
		{
			UnitsListView->AddItem(Unit);
		}
	}

	if (UnitStatus == EUnitStatus::Dissolved)
	{
		if (OwnerCountry == Unit->GetCountryOwner())
		{
			UnitsListView->RemoveItem(Unit);
		}
	}
}