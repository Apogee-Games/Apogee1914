#include "Widgets/Administration/Laws/LawButtonWidget.h"
#include "Characters/HUDs/HumanPlayerHUD.h"

void ULawButtonWidget::Init(ULawDescription* ProvidedLaw, ULawDescriptionWidget* ProvidedLawsSubgroupWidget)
{
	Button->OnClicked.AddDynamic(this, &ULawButtonWidget::OnButtonClick);
	Law = ProvidedLaw;
	LawNameTextBlock->SetText(Law->Name);
	LawDescriptionWidget = ProvidedLawsSubgroupWidget;
}

void ULawButtonWidget::OnButtonClick()
{
	LawDescriptionWidget->SetLaw(Law);
}
