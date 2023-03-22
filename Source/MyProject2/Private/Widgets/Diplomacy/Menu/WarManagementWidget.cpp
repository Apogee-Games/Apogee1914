
#include "Widgets/Diplomacy/Menu/WarManagementWidget.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/JoinOurWarPawnState.h"
#include "Characters/StateMachine/JoinTheirWarPawnState.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void UWarManagementWidget::Init()
{
	DeclareWarButton->OnClicked.AddDynamic(this, &UWarManagementWidget::OnDeclareWarButtonClick);
	AskThemToJoinWarButton->OnClicked.AddDynamic(this, &UWarManagementWidget::OnAskThemToJoinWarButtonClick);
	AskToJoinTheirWarButton->OnClicked.AddDynamic(this, &UWarManagementWidget::OnAskToJoinTheirWarButtonClick);

	OwnerCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
}

void UWarManagementWidget::SetCountry(UCountry* ProvidedCountry)
{
	Country = ProvidedCountry;
	RefreshData();
}

void UWarManagementWidget::RefreshData()
{
	URelationshipsManager* RelationshipsManager = GetGameInstance()->GetSubsystem<URelationshipsManager>();
	
	DeclareWarButton->SetIsEnabled(RelationshipsManager->CanDeclareWar(OwnerCountry, Country));

	WidgetSwitcher->SetActiveWidgetIndex(Country->GetAlliance()->IsCountryMember(OwnerCountry));
	
	if (RelationshipsManager->CanCountryJoinWar(Country, OwnerCountry))
	{
		AskThemToJoinWarButton->SetIsEnabled(RelationshipsManager->IsTherePossibleWarToJoin(Country, OwnerCountry));
		AskToJoinTheirWarButton->SetIsEnabled(RelationshipsManager->IsTherePossibleWarToJoin(OwnerCountry, Country));
	}
	else
	{
		AskThemToJoinWarButton->SetIsEnabled(false);
		AskToJoinTheirWarButton->SetIsEnabled(false);
	}
}

void UWarManagementWidget::OnDeclareWarButtonClick()
{
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->DeclareWar(OwnerCountry, Country);
}

void UWarManagementWidget::OnAskToJoinTheirWarButtonClick()
{
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetTheirWarsListWidget()->SetCountry(Country);
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FJoinTheirWarPawnState::GetInstance());
}

void UWarManagementWidget::OnAskThemToJoinWarButtonClick()
{
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetOurWarsListWidget()->SetCountry(Country);
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FJoinOurWarPawnState::GetInstance());
}
