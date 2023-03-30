#include "Widgets/Administration/Laws/LawButtonWidget.h"
#include "Characters/HUDs/HumanPlayerHUD.h"

void ULawButtonWidget::Init(FLawDescription* ProvidedLawDescription, ULawDescriptionWidget* ProvidedLawsSubgroupWidget)
{
	Button->OnClicked.AddDynamic(this, &ULawButtonWidget::OnButtonClick);
	LawDescription = ProvidedLawDescription;
	LawNameTextBlock->SetText(LawDescription->LawName);
	LawDescriptionWidget = ProvidedLawsSubgroupWidget;
}

void ULawButtonWidget::OnButtonClick()
{
	LawDescriptionWidget->SetLaw(LawDescription);
}
