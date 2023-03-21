#include "Widgets/Diplomacy/CountryDiplomacyWidget.h"

#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/AllianceCreationPawnState.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void UCountryDiplomacyWidget::Init()
{
	Lists.Add(War, EnemyCountriesListView);
	Lists.Add(NonAggressionPact, NonAggressionPactCountriesListView);
	Lists.Add(DefencivePact, DefencivePactCountriesListView);
	Lists.Add(Allied, AlliedCountriesListView);
	
	CreateNonAggressionPactButton->OnClicked.AddDynamic(this, &UCountryDiplomacyWidget::OnCreateNonAggressionPactButtonClick);
	DeclareWarButton->OnClicked.AddDynamic(this, &UCountryDiplomacyWidget::OnDeclareWarButtonClick);
	CreateDefencivePactButton->OnClicked.AddDynamic(this, &UCountryDiplomacyWidget::OnCreateDefencivePactButtonClick);
	CreateAllianceWithAnotherCountryButton->OnClicked.AddDynamic(this, &UCountryDiplomacyWidget::OnCreateAllianceWithAnotherButtonClick);
	CreateAllianceButton->OnClicked.AddDynamic(this, &UCountryDiplomacyWidget::OnCreateAllianceButtonClick);

	OwnerCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
}

void UCountryDiplomacyWidget::SetCountry(UCountry* ProvidedCountry)
{
	Country = ProvidedCountry;
	RefreshData();
}

void UCountryDiplomacyWidget::RefreshData()
{
	URelationshipsManager* RelationshipsManager = GetGameInstance()->GetSubsystem<URelationshipsManager>();

	if (OwnerCountry != Country)
	{
		CreateNonAggressionPactButton->SetIsEnabled(RelationshipsManager->CanCreateNonAggressionPact(OwnerCountry, Country));
		DeclareWarButton->SetIsEnabled(RelationshipsManager->CanDeclareWar(OwnerCountry, Country));
		CreateDefencivePactButton->SetIsEnabled(RelationshipsManager->CanCreateDefencivePact(OwnerCountry, Country));
		CreateAllianceWithAnotherCountryButton->SetIsEnabled(RelationshipsManager->CanCreateAlliance(OwnerCountry, Country));
		WidgetSwitcher->SetActiveWidgetIndex(0);
	} else
	{
		WidgetSwitcher->SetActiveWidgetIndex(1);
	}

	for (const auto& [Relation, List]: Lists)
	{
		List->ClearListItems();
	}
	
	for (const auto& [AnotherCountry, Relation] : RelationshipsManager->GetRelations(Country))
	{
		if (Relation == Neutral) continue;
		Lists[Relation]->AddItem(AnotherCountry);
	}

	CountryFlag->SetBrushResourceObject(Country->GetFlag());
	CountryNameTextBlock->SetText(FText::FromName(Country->GetName()));
}

void UCountryDiplomacyWidget::OnCreateNonAggressionPactButtonClick()
{
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->CreateNonAggressionPact(OwnerCountry, Country);
}

void UCountryDiplomacyWidget::OnDeclareWarButtonClick()
{
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->DeclareWar(OwnerCountry, Country);
}

void UCountryDiplomacyWidget::OnCreateDefencivePactButtonClick()
{
	GetGameInstance()->GetSubsystem<URelationshipsManager>()->CreateDefencivePact(OwnerCountry, Country);
}

void UCountryDiplomacyWidget::OnCreateAllianceWithAnotherButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FAllianceCreationPawnState::GetInstance());
	GetOwningPlayer<APlayerController>()->GetHUD<AHumanPlayerHUD>()->GetAllianceCreationWidget()->AddToBeInvitedCountry(Country);
}

void UCountryDiplomacyWidget::OnCreateAllianceButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FAllianceCreationPawnState::GetInstance());
}
