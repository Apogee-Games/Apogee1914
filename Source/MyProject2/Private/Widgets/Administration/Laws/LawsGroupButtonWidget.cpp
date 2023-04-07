#include "Widgets/Administration/Laws/LawsGroupButtonWidget.h"

#include "Administration/Descriptions/Law/LawsGroup.h"

void ULawsGroupButtonWidget::Init(ULawsGroup* LawsGroup, UWidgetSwitcher* ProvidedWidgetSwitcher, int32 ProvidedIndex)
{
	GroupButton->OnClicked.AddDynamic(this, &ULawsGroupButtonWidget::OnButtonClick);
	GroupTextBlock->SetText(LawsGroup->Name);
	WidgetSwitcher = ProvidedWidgetSwitcher;
	Index = ProvidedIndex;
}

void ULawsGroupButtonWidget::OnButtonClick()
{
	WidgetSwitcher->SetActiveWidgetIndex(Index);
}
