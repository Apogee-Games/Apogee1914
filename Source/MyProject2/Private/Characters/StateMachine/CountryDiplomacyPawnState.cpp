﻿
#include "Characters/StateMachine/CountryDiplomacyPawnState.h"

#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Maps/MapController.h"
#include "MyProject2/MyProject2.h"

TSharedPtr<FPawnState> FCountryDiplomacyPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FCountryDiplomacyPawnState>(new FCountryDiplomacyPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FCountryDiplomacyPawnState::LeftClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

TSharedPtr<FPawnState> FCountryDiplomacyPawnState::RightClick(APawn* ProvidedPawn)
{
	AHumanPlayerPawn* Pawn = Cast<AHumanPlayerPawn>(ProvidedPawn);

	FVector2d Point = Pawn->GetMapActor()->GetMapPosition(Pawn);
	
	UProvince* Province = ProvidedPawn->GetGameInstance()->GetSubsystem<UMapController>()->SelectProvince(Point);

	if (!Province) return Instance;

	FGlobalUIDelegates::OnCountrySelected.Broadcast(Province->GetCountryController());

	Pawn->GetGameInstance()->GetSubsystem<UMapController>()->SetCountryRelationMapAll(); // TODO: Add logic for one country

	return Instance;
}

bool FCountryDiplomacyPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UCountryDiplomacyWidget*>(Widget) != nullptr;
}

bool FCountryDiplomacyPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FCountryDiplomacyPawnState::FCountryDiplomacyPawnState()
{
}

