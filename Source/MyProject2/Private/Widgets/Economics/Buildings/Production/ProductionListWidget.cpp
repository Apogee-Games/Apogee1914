#include "Widgets/Economics/Buildings/Production/ProductionListWidget.h"

#include "Economics/Instances/Buildings/FactoryBuilding.h"
#include "Economics/Managers/BuildingManager.h"

void UProductionListWidget::Init()
{
	GetGameInstance()->GetSubsystem<UBuildingManager>()->AddBuildingCreationObserver(this);
}

void UProductionListWidget::BuildingIsCreated(UBuilding* Building)
{
	if (Cast<UFactoryBuilding>(Building))
	{
		FactoriesListView->AddItem(Building);
	}
}
