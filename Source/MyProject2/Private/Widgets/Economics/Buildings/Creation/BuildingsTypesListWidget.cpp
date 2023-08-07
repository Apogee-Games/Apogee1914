#include "Widgets/Economics/Buildings/Creation/BuildingsTypesListWidget.h"
#include "MyGameInstance.h"

void UBuildingsTypesListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (!BuildingsDescriptionScrollBox->GetChildrenCount())
	{
		for (const auto& Building: GetGameInstance<UMyGameInstance>()->ActiveScenario->BuildingsDescriptions)
		{
			AddBuilding(Building);
		}
	}
}

void UBuildingsTypesListWidget::AddBuilding(UBuildingDescription* BuildingDescription)
{
	UBuildingTypeDescriptionWidget* Widget = CreateWidget<UBuildingTypeDescriptionWidget>(GetOwningPlayer(), WidgetsClasses[BuildingDescription->Type]);
	Widget->Init(BuildingDescription);
	BuildingsDescriptionScrollBox->AddChild(Widget);
}
