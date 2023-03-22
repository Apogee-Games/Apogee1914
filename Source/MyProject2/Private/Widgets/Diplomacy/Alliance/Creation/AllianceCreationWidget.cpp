
#include "Widgets/Diplomacy/Alliance/Creation/AllianceCreationWidget.h"
#include "Administration/Instances/Country.h"
#include "Administration/Managers/CountriesManager.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void UAllianceCreationWidget::Init()
{
	CreateAllianceButton->OnClicked.AddDynamic(this, &UAllianceCreationWidget::OnCreateAllianceButtonClick);
}

void UAllianceCreationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
	InvitationalCountriesListView->ClearListItems();
	ToBeInvitedCountriesListView->ClearListItems();
	
	TArray<UCountry*> Countries;
	GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountryMap().GenerateValueArray(Countries);

	UCountry* OwnersCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
	
	for (const auto& Country: Countries)
	{
		if (Country == OwnersCountry) continue;
		InvitationalCountriesListView->AddItem(Country);
	}
}

void UAllianceCreationWidget::AddToBeInvitedCountry(UCountry* Country)
{
	InvitationalCountriesListView->RemoveItem(Country);
	ToBeInvitedCountriesListView->AddItem(Country);
}

void UAllianceCreationWidget::RemoveToBeInvitedCountry(UCountry* Country)
{
	InvitationalCountriesListView->AddItem(Country);
	ToBeInvitedCountriesListView->RemoveItem(Country);
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
