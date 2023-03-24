#include "Widgets/Administration/Laws/LawsSubgroupWidget.h"

void ULawsSubgroupWidget::Init(ULawDescriptionWidget* ProvidedLawDescriptionWidget, const FName& SubgroupName)
{
	LawDescriptionWidget = ProvidedLawDescriptionWidget;
	SubgroupNameTextBlock->SetText(FText::FromName(SubgroupName));
}

void ULawsSubgroupWidget::AddLaw(FLawDescription* LawDescription)
{
	ULawButtonWidget* LawButtonWidget = CreateWidget<ULawButtonWidget>(GetOwningPlayer(), LawButtonWidgetClass);
	LawButtonWidget->Init(LawDescription, LawDescriptionWidget);
	LawsButtonsScrollBox->AddChild(LawButtonWidget);
}
