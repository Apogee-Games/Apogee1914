#include "Widgets/Administration/Laws/LawsGroupWidget.h"
#include "Administration/Descriptions/LawDescription.h"

void ULawsGroupWidget::SelectLaw(FLawDescription* LawDescription)
{
	LawDescriptionWidget->SetLaw(LawDescription);
}

void ULawsGroupWidget::AddLaw(FLawDescription* LawDescription)
{
	if (!Subgroups.Contains(LawDescription->Subgroup))
	{
		ULawsSubgroupWidget* LawsSubgroupWidget = CreateWidget<ULawsSubgroupWidget>(GetOwningPlayer(), LawsSubgroupWidgetClass);
		LawsSubgroupWidget->Init(LawDescriptionWidget, LawDescription->Subgroup);
		Subgroups.Add(LawDescription->Subgroup, LawsSubgroupWidget);
		LawsSubgroupsScrollBox->AddChild(LawsSubgroupWidget);
	}
	Subgroups[LawDescription->Subgroup]->AddLaw(LawDescription);
}

void ULawsGroupWidget::Init(ULawDescriptionWidget* ProvidedLawDescriptionWidget)
{
	LawDescriptionWidget = ProvidedLawDescriptionWidget;
}
