
#include "Characters/StateMachine/CountryDiplomacyPawnState.h"

#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Maps/Diplomacy/CountryRelationMap.h"
#include "Maps/Selection/SelectionMap.h"

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
	USelectionMap* SelectionMap = ProvidedPawn->GetGameInstance()->GetSubsystem<USelectionMap>();

	AHumanPlayerPawn* Pawn = Cast<AHumanPlayerPawn>(ProvidedPawn);

	FVector2d Point = Pawn->MapActor->GetMapPosition(Pawn);
	
	UProvince* Province = SelectionMap->GetProvince(Point);

	if (!Province) return Instance;

	AHumanPlayerHUD* HUD = Pawn->GetController<APlayerController>()->GetHUD<AHumanPlayerHUD>();
	
	UCountryDiplomacyWidget* Widget = HUD->GetCountryDiplomacyWidget();
	
	Widget->SetCountry(Province->GetCountryController());

	Pawn->GetGameInstance()->GetSubsystem<UCountryRelationMap>()->UpdateMap(); // TODO: Add logic for one country

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

