#include "Widgets/Diplomacy/Menu/AllianceManagementWidget.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/AllianceCreationPawnState.h"
#include "Characters/StateMachine/CountryDiplomacyPawnState.h"
#include "Diplomacy/Instances/Alliance.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "MyProject2/MyProject2.h"

void UAllianceManagementWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FGlobalUIDelegates::OnCountrySelected.AddUObject(this, &ThisClass::OnCountrySelected);
	
	CreateAllianceWithAnotherCountryButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnCreateAllianceWithAnotherCountryButtonClick);
	CreateAllianceButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnCreateAllianceButtonClick);
	AskThemToJoinAllianceButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnAskThemToJoinAllianceButtonClick);
	AskToJoinTheirAllianceButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnAskToJoinTheirAllianceButtonClick);
	LeaveAllianceButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnLeaveAllianceButtonClick);
	DissolveAllianceButton->OnClicked.AddDynamic(this, &UAllianceManagementWidget::OnDissolveAllianceButtonClick);

	GetGameInstance()->GetSubsystem<URelationshipsManager>()->OnCountryRelationsTypeChanged.AddUObject(this, &ThisClass::OnCountryRelationsTypeChanged);
	
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	OwnerCountry = Pawn->GetRuledCountry();
	OnCountrySelected(Pawn->GetSelectedCountry());
}

void UAllianceManagementWidget::NativeDestruct()
{
	Super::NativeDestruct();

	FGlobalUIDelegates::OnCountrySelected.RemoveAll(this);
	
	CreateAllianceWithAnotherCountryButton->OnClicked.RemoveAll(this);
	CreateAllianceButton->OnClicked.RemoveAll(this);
	AskThemToJoinAllianceButton->OnClicked.RemoveAll(this);
	AskToJoinTheirAllianceButton->OnClicked.RemoveAll(this);
	LeaveAllianceButton->OnClicked.RemoveAll(this);
	DissolveAllianceButton->OnClicked.RemoveAll(this);

	GetGameInstance()->GetSubsystem<URelationshipsManager>()->OnCountryRelationsTypeChanged.RemoveAll(this);
}

void UAllianceManagementWidget::SetCountry(UCountry* ProvidedCountry)
{
	Country = ProvidedCountry;
	RefreshData();
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
	AHumanPlayerPawn* HumanPlayerPawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	HumanPlayerPawn->SetPawnState(FAllianceCreationPawnState::GetInstance());

	HumanPlayerPawn->OnCountryToBeInvitedToAllianceStatusChanged.Broadcast(Country, EToBeInvitedCountryStatus::Added);
}

void UAllianceManagementWidget::OnCreateAllianceButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FAllianceCreationPawnState::GetInstance());
}

void UAllianceManagementWidget::OnAskThemToJoinAllianceButtonClick()
{
	OwnerCountry->GetAlliance()->AddMember(Country);
}

void UAllianceManagementWidget::OnAskToJoinTheirAllianceButtonClick()
{
	Country->GetAlliance()->AddMember(OwnerCountry);
}

void UAllianceManagementWidget::OnLeaveAllianceButtonClick()
{
	OwnerCountry->GetAlliance()->RemoveMember(OwnerCountry);
}

void UAllianceManagementWidget::OnDissolveAllianceButtonClick()
{
	OwnerCountry->GetAlliance()->Dissolve();
}

void UAllianceManagementWidget::OnCountryRelationsTypeChanged(UCountry* ProbableOwner, UCountry* ProbableCountry, ERelationType Relation)
{
	if (OwnerCountry == ProbableOwner && Country == ProbableCountry)
	{
		RefreshData();
	}
}

void UAllianceManagementWidget::OnCountrySelected(UCountry* InCountry)
{
	Country = InCountry;
	RefreshData();
}
