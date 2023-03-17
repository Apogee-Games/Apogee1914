#include "Widgets/CountrySelection/SelectedCountryWidget.h"

void USelectedCountryWidget::SetCountry(UCountry* Country)
{
	CountryFlagImage->SetBrushResourceObject(Country->GetFlag());
	CountryNameTextBlock->SetText(FText::FromName(Country->GetName()));
	//RulingFractionNameTextBlock->SetText(FText::FromName(Country->))
}
