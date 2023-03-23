
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
	DeclareWarButton->SetIsEnabled(OwnerCountry->CanDeclareWarOn(Country));

	WidgetSwitcher->SetActiveWidgetIndex(Country->IsInAlliance() && Country->GetAlliance()->IsCountryMember(OwnerCountry));
	
	if (Country->CanJoinCountryWar(OwnerCountry))
	{
		AskThemToJoinWarButton->SetIsEnabled(OwnerCountry->CanCountryJoinOneOfOurWars(Country));
		AskToJoinTheirWarButton->SetIsEnabled(Country->CanCountryJoinOneOfOurWars(OwnerCountry));
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
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FJoinTheirWarPawnState::GetInstance());
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetTheirWarsListWidget()->SetCountry(Country);
}

void UWarManagementWidget::OnAskThemToJoinWarButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FJoinOurWarPawnState::GetInstance());
	GetOwningPlayer()->GetHUD<AHumanPlayerHUD>()->GetOurWarsListWidget()->SetCountry(Country);
}
