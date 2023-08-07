#include "Characters/StateMachine/MapBrowsingPawnState.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/StateMachine/CountryDiplomacyPawnState.h"
#include "Maps/MapController.h"
#include "MyProject2/MyProject2.h"

TSharedPtr<FPawnState> FMapBrowsingPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FMapBrowsingPawnState>(new FMapBrowsingPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FMapBrowsingPawnState::LeftClick(APawn* ProvidedPawn)
{
	AHumanPlayerPawn* Pawn = Cast<AHumanPlayerPawn>(ProvidedPawn);

	UMapController* MapController = Pawn->GetWorld()->GetGameInstance()->GetSubsystem<UMapController>();
	UProvince* Province = MapController->SelectProvince(Pawn->GetMapActor()->GetMapPosition(Pawn));

	FGlobalUIDelegates::OnProvinceSelected.Broadcast(Province);

	Pawn->UnitSelectionComponent->ClearSelectedUnits();
	
	return Instance;
}

TSharedPtr<FPawnState> FMapBrowsingPawnState::RightClick(APawn* ProvidedPawn)
{
	return FCountryDiplomacyPawnState::GetInstance()->RightClick(ProvidedPawn);
}

bool FMapBrowsingPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UProvinceDataWidget*>(Widget) != nullptr;
}

bool FMapBrowsingPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FMapBrowsingPawnState::FMapBrowsingPawnState()
{
}
