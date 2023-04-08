#include "Widgets/Administration/Country/FractionWidget.h"

void UFractionWidget::SetFraction(UObject* ProvidedFraction)
{
	Fraction = Cast<UFraction>(ProvidedFraction);
}

void UFractionWidget::RefreshData()
{
	FractionNameTextBlock->SetText(Fraction->GetFractionName());
	FractionNameTextBlock->SetColorAndOpacity(Fraction->GetIdeology()->Color);
	MembersNumberTextBlock->SetText(FText::FromString(FString::FromInt(Fraction->GetMembersNumber())));
}
