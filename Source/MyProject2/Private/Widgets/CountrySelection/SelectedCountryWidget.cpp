#include "Widgets/CountrySelection/SelectedCountryWidget.h"

void USelectedCountryWidget::SetCountry(UCountry* Country)
{
	CountryFlagImage->SetBrushResourceObject(Country->GetFlag());
	CountryNameTextBlock->SetText(Country->GetName());

	UPerson* Ruler = Country->GetRuler();

	RulerImage->SetBrushResourceObject(Ruler->GetImage());
	RulerNameTextBlock->SetText(Ruler->GetPersonName());

	//RulingFractionNameTextBlock->SetText(FText::FromName(Country->))
}
