﻿#include "Widgets/Diplomacy/Menu/CountryFlagWidget.h"

void UCountryFlagWidget::SetCountry(UObject* ProvidedCountry)
{
	Country = Cast<UCountry>(ProvidedCountry);
}

void UCountryFlagWidget::RefreshData()
{
	CountryFlagImage->SetBrushResourceObject(Country->GetFlag());
}
