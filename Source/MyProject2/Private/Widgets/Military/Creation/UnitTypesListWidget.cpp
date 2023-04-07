
#include "Widgets/Military/Creation/UnitTypesListWidget.h"

#include "Military/Managers/UnitsFactory.h"

void UUnitTypesListWidget::Init()
{
	const TArray<UUnitDescription*>& UnitDescriptions = GetGameInstance()->GetSubsystem<UUnitsFactory>()->GetUnitsDescriptions();
	for (const auto& UnitDescription: UnitDescriptions)
	{
		AddUnitType(UnitDescription);
	}
}

void UUnitTypesListWidget::AddUnitType(UUnitDescription* UnitDescription)
{
	UnitDescriptionListView->AddItem(UnitDescription);
}
