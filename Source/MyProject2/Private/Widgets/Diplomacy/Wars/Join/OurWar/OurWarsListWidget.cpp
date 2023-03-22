#include "Widgets/Diplomacy/Wars/Join/OurWar/OurWarsListWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"


void UOurWarsListWidget::SetCountry(UCountry* ProvidedCountry)
{
	Country = ProvidedCountry;
	UCountry* OwnerCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
	
	WarsListView->ClearListItems();
	for (const auto War: OwnerCountry->GetWars())
	{
		if (!War->IsMember(Country))
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