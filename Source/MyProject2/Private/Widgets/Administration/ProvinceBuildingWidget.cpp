
#include "Widgets/Administration/ProvinceBuildingWidget.h"

void UProvinceBuildingWidget::SetBuilding(UObject* ProvidedBuilding)
{
	Building = Cast<UBuilding>(ProvidedBuilding);
}

void UProvinceBuildingWidget::RefreshData()
{
	BuildingNameTextBlock->SetText(FText::FromName(Building->GetBuildingName()));
	LabourTextBlock->SetText(FText::FromString(FString::FromInt(Building->GetLabours())));
	MaxLabourTextBlock->SetText(FText::FromString(FString::FromInt(Building->GetMaxLabours())));
}
