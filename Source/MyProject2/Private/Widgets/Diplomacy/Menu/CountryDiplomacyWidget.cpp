#include "Widgets/Diplomacy/Menu/CountryDiplomacyWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "MyProject2/MyProject2.h"

void UCountryDiplomacyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	OwnerCountry = Pawn->GetRuledCountry();
	OnCountrySelected(Pawn->GetSelectedCountry());
	
	FGlobalUIDelegates::OnCountrySelected.AddUObject(this, &ThisClass::OnCountrySelected);
}

void UCountryDiplomacyWidget::NativeDestruct()
{
	Super::NativeDestruct();

	FGlobalUIDelegates::OnCountrySelected.RemoveAll(this);
}

void UCountryDiplomacyWidget::OnCountrySelected(UCountry* InCountry)
{
	Country = InCountry;
	RefreshData();
}

void UCountryDiplomacyWidget::RefreshData()
{
	if (Country == OwnerCountry)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
	} else
	{
		WidgetSwitcher->SetActiveWidgetIndex(1);
	}
	
	CountryFlag->SetBrushResourceObject(Country->GetFlag());
	CountryNameTextBlock->SetText(Country->GetName());
}
