#include "Widgets/Military/Creation/UnitTypesListWidget.h"
#include "Military/Managers/UnitsFactory.h"

void UUnitTypesListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!UnitDescriptionListView->GetNumItems())
	{
		UUnitsFactory* UnitsFactory = GetGameInstance()->GetSubsystem<UUnitsFactory>();
		const TArray<UUnitDescription*>& UnitDescriptions = UnitsFactory->GetUnitsDescriptions();
		for (const auto& UnitDescription: UnitDescriptions)
		{
			UnitDescriptionListView->AddItem(UnitDescription);
		}
	}
}