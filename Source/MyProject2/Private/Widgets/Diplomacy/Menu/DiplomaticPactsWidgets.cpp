#include "Widgets/Diplomacy/Menu/DiplomaticPactsWidgets.h"
#include "Administration/Instances/Country.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void UDiplomaticPactsWidgets::Init()
{
	CreateNonAggressionPactButton->OnClicked.AddDynamic(this, &UDiplomaticPactsWidgets::OnCreateNonAggressionPactButtonClick);
	BreakNonAggressionPactButton->OnClicked.AddDynamic(this, &UDiplomaticPactsWidgets::OnBreakNonAggressionPactButtonClick);
	CreateDefencivePactButton->OnClicked.AddDynamic(this, &UDiplomaticPactsWidgets::OnCreateDefencivePactButtonClick);
	BreakDefencivePactButton->OnClicked.AddDynamic(this, &UDiplomaticPactsWidgets::OnBreakDefencivePactButtonClick);
	
	OwnerCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
}

void UDiplomaticPactsWidgets::SetCountry(UCountry* ProvidedCountry)
{
	Country = ProvidedCountry;
	RefreshData();
}

void UDiplomaticPactsWidgets::RefreshData()
{
	if (OwnerCountry->HasNonAggressionPactWith(Country)) {
		NonAggressionPactCreationRemovalWidgetSwitcher->SetActiveWidgetIndex(1);
		BreakDefencivePactButton->SetIsEnabled(true); // TODO: Maybe some additional logic here :) ?
	} else
	{
		NonAggressionPactCreationRemovalWidgetSwitcher->SetActiveWidgetIndex(0);
		CreateNonAggressionPactButton->SetIsEnabled(OwnerCountry->CanCreateNonAggressionPactWith(Country));
	}
	
	if (OwnerCountry->HasDefencivePactWith(Country))
	{
		DefencivePactCreationRemovalWidgetSwitcher->SetActiveWidgetIndex(1);
		BreakDefencivePactButton->SetIsEnabled(true);  // TODO: Maybe some additional logic here :) ?
	} else
	{
		DefencivePactCreationRemovalWidgetSwitcher->SetActiveWidgetIndex(0);
		CreateDefencivePactButton->SetIsEnabled(OwnerCountry->CanCreateDefencivePactWith(Country));
	}
}

void UDiplomaticPactsWidgets::OnCreateNonAggressionPactButtonClick()
{
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->CreateNonAggressionPact(OwnerCountry, Country);
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetCountryDiplomacyWidget()->RefreshData();
}

void UDiplomaticPactsWidgets::OnBreakNonAggressionPactButtonClick()
{
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->BreakNonAggressionPact(OwnerCountry, Country);
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetCountryDiplomacyWidget()->RefreshData();
}

void UDiplomaticPactsWidgets::OnCreateDefencivePactButtonClick()
{
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->CreateDefencivePact(OwnerCountry, Country);
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetCountryDiplomacyWidget()->RefreshData();
}

void UDiplomaticPactsWidgets::OnBreakDefencivePactButtonClick()
{
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->BreakDefencivePact(OwnerCountry, Country);
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetCountryDiplomacyWidget()->RefreshData();
}