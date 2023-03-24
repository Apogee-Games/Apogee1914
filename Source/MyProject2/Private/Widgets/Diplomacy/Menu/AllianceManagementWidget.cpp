#include "Widgets/Diplomacy/Menu/AllianceManagementWidget.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/AllianceCreationPawnState.h"
#include "Characters/StateMachine/CountryDiplomacyPawnState.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void UAllianceManagementWidget::SetCountry(UCountry* ProvidedCountry)
{
	Country = ProvidedCountry;
	RefreshData();
}

void UAllianceManagementWidget::Init()
{
	CreateAllianceWithAnotherCountryButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnCreateAllianceWithAnotherCountryButtonClick);
	CreateAllianceButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnCreateAllianceButtonClick);
	AskThemToJoinAllianceButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnAskThemToJoinAllianceButtonClick);
	AskToJoinTheirAllianceButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnAskToJoinTheirAllianceButtonClick);
	LeaveAllianceButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnLeaveAllianceButtonClick);
	DissolveAllianceButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnDissolveAllianceButtonClick);
	OwnerCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
}

void UAllianceManagementWidget::RefreshData()
{
	if (OwnerCountry == Country)
	{
		AllianceInteractionsWidgetSwitcher->SetActiveWidgetIndex(0);
		if (OwnerCountry->IsInAlliance())
		{
			AllianceCreationDeletionWidgetSwitcher->SetActiveWidgetIndex(1);
			LeaveAllianceButton->SetIsEnabled(OwnerCountry->GetAlliance()->Size() > 1);
			DissolveAllianceButton->SetIsEnabled(OwnerCountry->GetAlliance()->IsCountryLeader(OwnerCountry));
		} else
		{
			AllianceCreationDeletionWidgetSwitcher->SetActiveWidgetIndex(0);
			CreateAllianceButton->SetIsEnabled(!OwnerCountry->IsNonAligned());
		}
	} else if (OwnerCountry->IsInAlliance() && Country->IsInAlliance())
	{
		AllianceInteractionsWidgetSwitcher->SetActiveWidgetIndex(2);
		AskThemToJoinAllianceButton->SetIsEnabled(false);
		AskToJoinTheirAllianceButton->SetIsEnabled(false);
	} else if (OwnerCountry->IsInAlliance() || Country->IsInAlliance())
	{
		AllianceInteractionsWidgetSwitcher->SetActiveWidgetIndex(2);
		AskThemToJoinAllianceButton->SetIsEnabled(OwnerCountry->IsInAlliance() && OwnerCountry->GetAlliance()->CountryCanJoin(Country)); 
		AskToJoinTheirAllianceButton->SetIsEnabled(Country->IsInAlliance() && Country->GetAlliance()->CountryCanJoin(OwnerCountry));
	} else 
	{
		AllianceInteractionsWidgetSwitcher->SetActiveWidgetIndex(1);
		CreateAllianceWithAnotherCountryButton->SetIsEnabled(OwnerCountry->CanCreateAllianceWith(Country));
	}
}

void UAllianceManagementWidget::OnCreateAllianceWithAnotherCountryButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FAllianceCreationPawnState::GetInstance());
	GetOwningPlayer<APlayerController>()->GetHUD<AHumanPlayerHUD>()->GetAllianceCreationWidget()->AddToBeInvitedCountry(Country);
}

void UAllianceManagementWidget::OnCreateAllianceButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FAllianceCreationPawnState::GetInstance());
}

void UAllianceManagementWidget::OnAskThemToJoinAllianceButtonClick()
{
	OwnerCountry->GetAlliance()->AddMember(Country);
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetCountryDiplomacyWidget()->RefreshData();
}

void UAllianceManagementWidget::OnAskToJoinTheirAllianceButtonClick()
{
	Country->GetAlliance()->AddMember(OwnerCountry);
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetCountryDiplomacyWidget()->RefreshData();
}

void UAllianceManagementWidget::OnLeaveAllianceButtonClick()
{
	OwnerCountry->GetAlliance()->RemoveMember(OwnerCountry);
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetCountryDiplomacyWidget()->RefreshData();
}

void UAllianceManagementWidget::OnDissolveAllianceButtonClick()
{
	OwnerCountry->GetAlliance()->Dissolve();
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetCountryDiplomacyWidget()->RefreshData();
}
