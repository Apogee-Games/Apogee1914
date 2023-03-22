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
	CreateAllianceWithAnotherCountryButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnCreateAllianceWithAnotherButtonClick);
	CreateAllianceButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnCreateAllianceButtonClick);
	OwnerCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
}

void UAllianceManagementWidget::RefreshData()
{
	URelationshipsManager* RelationshipsManager = GetGameInstance()->GetSubsystem<URelationshipsManager>();
	if (OwnerCountry->GetAlliance())
	{
		AllianceInteractionsWidgetSwitcher->SetActiveWidgetIndex(1);
		AskThemToJoinAllianceButton->SetIsEnabled(!Country->IsInAlliance());
	} else
	{
		AllianceInteractionsWidgetSwitcher->SetActiveWidgetIndex(0);
		CreateAllianceWithAnotherCountryButton->SetIsEnabled(!Country->IsInAlliance() && RelationshipsManager->CanCreateAlliance(OwnerCountry, Country));
	}
}

void UAllianceManagementWidget::OnCreateAllianceWithAnotherButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FAllianceCreationPawnState::GetInstance());
	GetOwningPlayer<APlayerController>()->GetHUD<AHumanPlayerHUD>()->GetAllianceCreationWidget()->AddToBeInvitedCountry(Country);
}

void UAllianceManagementWidget::OnCreateAllianceButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FAllianceCreationPawnState::GetInstance());
}

void UAllianceManagementWidget::OnAskToJoinAllianceButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FCountryDiplomacyPawnState::GetInstance());
	OwnerCountry->GetAlliance()->AddMember(Country);
}