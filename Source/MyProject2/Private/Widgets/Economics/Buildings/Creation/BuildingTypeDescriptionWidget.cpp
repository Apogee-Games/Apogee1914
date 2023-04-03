#include "Widgets/Economics/Buildings/Creation/BuildingTypeDescriptionWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

void UBuildingTypeDescriptionWidget::OnButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SelectBuildingDescription(BuildingDescription);
}

void UBuildingTypeDescriptionWidget::Init(UBuildingDescription* ProvidedBuildingDescription)
{
	BuildingDescription = ProvidedBuildingDescription;
	BuildingNameTextBlock->SetText(BuildingDescription->Name);

	Button->OnClicked.AddDynamic(this, &UBuildingTypeDescriptionWidget::OnButtonClick);
}

