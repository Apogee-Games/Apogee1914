#include "Widgets/Diplomacy/Wars/Join/TheirWar/TheirWarsListWidget.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/CountryDiplomacyPawnState.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Diplomacy/Instances/War.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void UTheirWarsListWidget::SetCountry(UCountry* ProvidedCountry)
{
	Country = ProvidedCountry;
	UCountry* OurCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();

	const TArray<UWar*> Wars = GetGameInstance()->GetSubsystem<URelationshipsManager>()->GetCountryWars(Country);
	WarsListView->ClearListItems();
	for (const auto War: Wars)
	{
		if (!War->CountryParticipates(OurCountry))
		{
			WarsListView->AddItem(War);
		}
	}
}

void UTheirWarsListWidget::SetSelectedWar(UWar* War)
{
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	War->AddCountryOnSide(Pawn->GetRuledCountry(), Country);
	Pawn->SetPawnState(FMapBrowsingPawnState::GetInstance());
}