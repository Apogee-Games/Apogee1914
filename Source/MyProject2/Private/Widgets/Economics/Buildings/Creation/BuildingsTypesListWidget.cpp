#include "Widgets/Economics/Buildings/Creation/BuildingsTypesListWidget.h"


void UBuildingsTypesListWidget::Init(const TArray<UBuildingDescription*>& BuildingDescriptions)
{
	for (const auto& Building: BuildingDescriptions)
	{
		AddBuilding(Building);
	}
}

void UBuildingsTypesListWidget::AddBuilding(UBuildingDescription* BuildingDescription)
{
	UBuildingTypeDescriptionWidget* Widget = CreateWidget<UBuildingTypeDescriptionWidget>(GetOwningPlayer(), WidgetsClasses[BuildingDescription->Type]);
	Widget->Init(BuildingDescription);
	BuildingsDescriptionScrollBox->AddChild(Widget);
}
