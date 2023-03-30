#include "Widgets/Diplomacy/Wars/Join/TheirWar/TheirWarsListWidget.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Diplomacy/Instances/War.h"

void UTheirWarsListWidget::SetCountry(UCountry* ProvidedCountry)
{
	Country = ProvidedCountry;
	UCountry* OwnerCountry = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();

	WarsListView->ClearListItems();
	for (const auto War: Country->GetWars())
	{
		if (!War->IsMember(OwnerCountry))
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
	// TODO: Move to item :)
}