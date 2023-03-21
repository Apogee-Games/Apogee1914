#include "Widgets/Diplomacy/Wars/Join/OurWar/OurWarsListWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/CountryDiplomacyPawnState.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Diplomacy/Managers/RelationshipsManager.h"


void UOurWarsListWidget::SetCountry(UCountry* ProvidedCountry)
{
	Country = ProvidedCountry;
	UCountry* OurCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
	
	const TArray<UWar*> Wars = GetGameInstance()->GetSubsystem<URelationshipsManager>()->GetCountryWars(OurCountry);
	
	WarsListView->ClearListItems();
	for (const auto War: Wars)
	{
		if (!War->CountryParticipates(Country))
		{
			WarsListView->AddItem(War);
		}
	}
}

void UOurWarsListWidget::SetSelectedWar(UWar* War)
{
	AHumanPlayerPawn* Pawn = GetOwningPlayerPawn<AHumanPlayerPawn>();
	War->AddCountryOnSide(Country, Pawn->GetRuledCountry());
	Pawn->SetPawnState(FMapBrowsingPawnState::GetInstance());
}