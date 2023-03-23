
#include "Widgets/Diplomacy/Wars/Description/WarParticipantWidget.h"

void UWarParticipantWidget::SetCountry(UObject* ProvidedCountry)
{
	Country = Cast<UCountry>(ProvidedCountry);
}

void UWarParticipantWidget::RefreshData()
{
	FlagImage->SetBrushResourceObject(Country->GetFlag());
	NameTextBlock->SetText(FText::FromName(Country->GetName()));
}
