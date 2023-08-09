
#include "Widgets/Diplomacy/Menu/WarManagementWidget.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/JoinOurWarPawnState.h"
#include "Characters/StateMachine/JoinTheirWarPawnState.h"
#include "Diplomacy/Instances/Alliance.h"
#include "Diplomacy/Managers/RelationshipsManager.h"
#include "MyProject2/MyProject2.h"

void UWarManagementWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FGlobalUIDelegates::OnCountrySelected.AddUObject(this, &ThisClass::OnCountrySelected);
	
	DeclareWarButton->OnClicked.AddDynamic(this, &ThisClass::OnDeclareWarButtonClick);
	AskThemToJoinWarButton->OnClicked.AddDynamic(this, &ThisClass::OnAskThemToJoinWarButtonClick);
	AskToJoinTheirWarButton->OnClicked.AddDynamic(this, &ThisClass::OnAskToJoinTheirWarButtonClick);

	GetGameInstance()->GetSubsystem<URelationshipsManager>()->OnCountryRelationsTypeChanged.AddUObject(this, &ThisClass::OnCountryRelationsTypeChanged);
	
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	OwnerCountry = Pawn->GetRuledCountry();
	OnCountrySelected(Pawn->GetSelectedCountry());
}

void UWarManagementWidget::NativeDestruct()
{
	Super::NativeDestruct();

	FGlobalUIDelegates::OnCountrySelected.RemoveAll(this);
	
	DeclareWarButton->OnClicked.RemoveAll(this);
	AskThemToJoinWarButton->OnClicked.RemoveAll(this);
	AskToJoinTheirWarButton->OnClicked.RemoveAll(this);

	GetGameInstance()->GetSubsystem<URelationshipsManager>()->OnCountryRelationsTypeChanged.RemoveAll(this);
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
}

void UWarManagementWidget::OnAskThemToJoinWarButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SetPawnState(FJoinOurWarPawnState::GetInstance());
}

void UWarManagementWidget::OnCountryRelationsTypeChanged(UCountry* ProbableOwner, UCountry* ProbableCountry, ERelationType Relation)
{
	if (OwnerCountry == ProbableOwner && Country == ProbableCountry)
	{
		RefreshData();
	}
}

void UWarManagementWidget::OnCountrySelected(UCountry* InCountry)
{
	Country = InCountry;
	RefreshData();
}
