#include "Widgets/Administration/Laws/LawsSubgroupWidget.h"

#include "Administration/Descriptions/Law/LawsSubgroup.h"

void ULawsSubgroupWidget::Init(ULawsSubgroup* LawsSubgroup, ULawDescriptionWidget* ProvidedLawDescriptionWidget)
{
	LawDescriptionWidget = ProvidedLawDescriptionWidget;
	SubgroupNameTextBlock->SetText(LawsSubgroup->Name);
	
	for (auto& Law: LawsSubgroup->Laws)
	{
		ULawButtonWidget* LawButtonWidget = CreateWidget<ULawButtonWidget>(GetOwningPlayer(), LawButtonWidgetClass);
		LawButtonWidget->Init(Law, LawDescriptionWidget);
		LawsButtonsScrollBox->AddChild(LawButtonWidget);
	}
}

