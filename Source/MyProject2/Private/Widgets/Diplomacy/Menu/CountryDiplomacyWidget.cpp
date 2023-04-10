#include "Widgets/Diplomacy/Menu/CountryDiplomacyWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

void UCountryDiplomacyWidget::Init()
{
	DiplomaticPactsWidget->Init();
	WarManagementWidget->Init();
	RelationsListWidget->Init();
	AllianceManagementWidget->Init();
	
	OwnerCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
}

void UCountryDiplomacyWidget::SetCountry(UCountry* ProvidedCountry)
{
	Country = ProvidedCountry;

	DiplomaticPactsWidget->SetCountry(ProvidedCountry);
	WarManagementWidget->SetCountry(ProvidedCountry);
	RelationsListWidget->SetCountry(ProvidedCountry);
	AllianceManagementWidget->SetCountry(ProvidedCountry);
	
	RefreshData();
}

void UCountryDiplomacyWidget::RefreshData()
{
	AllianceManagementWidget->RefreshData();

	if (Country == OwnerCountry)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
	} else
	{
		WidgetSwitcher->SetActiveWidgetIndex(1);
		DiplomaticPactsWidget->RefreshData();
		WarManagementWidget->RefreshData();
		RelationsListWidget->RefreshData();
	}
	
	CountryFlag->SetBrushResourceObject(Country->GetFlag());
	CountryNameTextBlock->SetText(Country->GetName());
}
