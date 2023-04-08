#include "Widgets/Administration/Country/CountryManagementWidget.h"
#include "Administration/Instances/Country.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

void UCountryManagementWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UCountry* Country = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
	
	RulerImage->SetBrushResourceObject(Country->GetRuler()->GetImage());
	RulerNameTextBlock->SetText(Country->GetRuler()->GetPersonName());

	IdeologyNameTextBlock->SetText(Country->GetIdeology()->Name);
	
	UParliament* FirstChamberParliament = Country->GetFirstChamber();
	
	if (FirstChamberParliament)
	{
		FirstChamberParliamentWidget->SetParliament(FirstChamberParliament);
		FirstChamberParliamentWidgetSwitcher->SetActiveWidgetIndex(0);
	} else
	{
		FirstChamberParliamentWidgetSwitcher->SetActiveWidgetIndex(1);
	}

	
	UParliament* SecondChamberParliament = Country->GetSecondChamber();
	
	if (SecondChamberParliament)
	{
		SecondChamberParliamentWidget->SetParliament(SecondChamberParliament);
		SecondChamberParliamentWidgetSwitcher->SetActiveWidgetIndex(0);
	} else
	{
		SecondChamberParliamentWidgetSwitcher->SetActiveWidgetIndex(1);
	}

}
