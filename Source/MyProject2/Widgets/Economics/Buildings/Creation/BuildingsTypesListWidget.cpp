#include "BuildingsTypesListWidget.h"

#include "MyProject2/Widgets/Economics/Carriers/BuildingDescriptionCarrier.h"

void UBuildingsTypesListWidget::AddBuildingType(FBuildingDescription* BuildingDescription)
{
	UBuildingDescriptionCarrier* Carrier = NewObject<UBuildingDescriptionCarrier>();
	Carrier->Init(BuildingDescription);
	BuildingDescriptionListView->AddItem(Carrier);
}
