#include "Widgets/Administration/Laws/LawConditionWidget.h"

void ULawConditionWidget::SetCondition(const FCondition& Condition, bool IsFulfilled)
{
	ConditionDescriptionMultiLineEditableText->SetText(Condition.Description);
	if (IsFulfilled)
	{
		ConditionDescriptionMultiLineEditableText->WidgetStyle.ColorAndOpacity = FulfilledConditionColor;
	} else
	{
		ConditionDescriptionMultiLineEditableText->WidgetStyle.ColorAndOpacity = NotFulfilledConditionColor;
	}
}
