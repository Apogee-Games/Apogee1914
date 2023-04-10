#include "Widgets/Administration/Laws/LawsGroupWidget.h"
#include "Administration/Descriptions/Law/LawsGroup.h"

void ULawsGroupWidget::Init(ULawsGroup* LawsGroup, ULawDescriptionWidget* ProvidedLawDescriptionWidget)
{
	LawDescriptionWidget = ProvidedLawDescriptionWidget;
	for (auto& LawsSubgroup: LawsGroup->Subgroups)
	{
		AddLawsSubgroup(LawsSubgroup);
	}
}

void ULawsGroupWidget::AddLawsSubgroup(ULawsSubgroup* LawsSubgroup)
{
	ULawsSubgroupWidget* LawsSubgroupWidget = CreateWidget<ULawsSubgroupWidget>(GetOwningPlayer(), LawsSubgroupWidgetClass);
	LawsSubgroupWidget->Init(LawsSubgroup, LawDescriptionWidget);
	LawsSubgroupsScrollBox->AddChild(LawsSubgroupWidget);
}
