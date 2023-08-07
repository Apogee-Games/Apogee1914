
#include "Widgets/Diplomacy/Alliance/Creation/AllianceCreationWidget.h"
#include "Administration/Instances/Country.h"
#include "Administration/Managers/CountriesManager.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void UAllianceCreationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AHumanPlayerPawn* HumanPlayerPawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	HumanPlayerPawn->OnCountryToBeInvitedToAllianceStatusChanged.AddUObject(this, &ThisClass::OnCountryToBeInvitedToAllianceStatusChanged);
	
	CreateAllianceButton->OnClicked.AddDynamic(this, &UAllianceCreationWidget::OnCreateAllianceButtonClick);
	
	InvitationalCountriesListView->ClearListItems();
	ToBeInvitedCountriesListView->ClearListItems();
	
	UCountry* OwnersCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
	
	for (const auto& [Description, Country]: GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountryMap())
	{
		if (Country == OwnersCountry) continue;
		InvitationalCountriesListView->AddItem(Country); // TODO: Add filtering of some sort
	}
}

void UAllianceCreationWidget::NativeDestruct()
{
	Super::NativeDestruct();

	CreateAllianceButton->OnClicked.RemoveAll(this);

	AHumanPlayerPawn* HumanPlayerPawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	HumanPlayerPawn->OnCountryToBeInvitedToAllianceStatusChanged.RemoveAll(this);
}

void UAllianceCreationWidget::OnCreateAllianceButtonClick()
{
	URelationshipsManager* RelationshipsManager = GetGameInstance()->GetSubsystem<URelationshipsManager>();

	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	
	UCountry* AllianceLeader = Pawn->GetRuledCountry();
	FText AllianceName = AllianceNameTextBlock->GetText(); 

	TArray<UCountry*> InvitedCountries;

	for (const auto& Country: ToBeInvitedCountriesListView->GetListItems())
	{
		InvitedCountries.Add(Cast<UCountry>(Country));
	}
	
	RelationshipsManager->CreateAlliance(AllianceLeader, AllianceName, InvitedCountries);

	Pawn->SetPawnState(FMapBrowsingPawnState::GetInstance());
}

void UAllianceCreationWidget::OnCountryToBeInvitedToAllianceStatusChanged(UCountry* Country, EToBeInvitedCountryStatus ToBeInvitedCountryStatus)
{
	if (ToBeInvitedCountryStatus == EToBeInvitedCountryStatus::Added)
	{
		InvitationalCountriesListView->RemoveItem(Country);
		ToBeInvitedCountriesListView->AddItem(Country);
	}
	if (ToBeInvitedCountryStatus == EToBeInvitedCountryStatus::Removed)
	{
		InvitationalCountriesListView->AddItem(Country);
		ToBeInvitedCountriesListView->RemoveItem(Country);
	}
}
