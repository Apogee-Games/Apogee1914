#include "Widgets/Administration/Laws/LawsGroupButtonWidget.h"

void ULawsGroupButtonWidget::Init(const FName& GroupName, UWidgetSwitcher* ProvidedWidgetSwitcher, int32 ProvidedIndex)
{
	GroupButton->OnClicked.AddDynamic(this, &ULawsGroupButtonWidget::OnButtonClick);
	GroupTextBlock->SetText(FText::FromName(GroupName));
	WidgetSwitcher = ProvidedWidgetSwitcher;
	Index = ProvidedIndex;
}

void ULawsGroupButtonWidget::OnButtonClick()
{
	WidgetSwitcher->SetActiveWidgetIndex(Index);
}
