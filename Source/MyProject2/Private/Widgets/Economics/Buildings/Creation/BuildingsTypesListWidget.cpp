

#include "Widgets/Economics/Buildings/Creation/BuildingsTypesListWidget.h"
#include "Widgets/Economics/Buildings/Carriers/BuildingDescriptionCarrier.h"

void UBuildingsTypesListWidget::AddBuildingType(FBuildingDescription* BuildingDescription)
{
	UBuildingDescriptionCarrier* Carrier = NewObject<UBuildingDescriptionCarrier>();
	Carrier->Init(BuildingDescription);
	BuildingDescriptionListView->AddItem(Carrier);
}
