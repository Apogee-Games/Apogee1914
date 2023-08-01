#include "Characters/StateMachine/CountrySelectionPawnState.h"

#include "MyGameInstance.h"
#include "Characters/HUDs/CountrySelectionHUD.h"
#include "Characters/Pawns/CountrySelectionPawn.h"
#include "Maps/MapController.h"

TSharedPtr<FPawnState> FCountrySelectionPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FCountrySelectionPawnState>(new FCountrySelectionPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FCountrySelectionPawnState::LeftClick(APawn* ProvidedPawn)
{
	ACountrySelectionPawn* Pawn = Cast<ACountrySelectionPawn>(ProvidedPawn);
	
	FVector2d Point = Pawn->GetMapActor()->GetMapPosition(Pawn);
	
	UProvince* Province = ProvidedPawn->GetGameInstance()->GetSubsystem<UMapController>()->SelectProvince(Point);

	if (Province && Province->GetOwnerCountry())
	{
		APlayerController* PlayerController = Pawn->GetController<APlayerController>();
		ACountrySelectionHUD* CountrySelectionHUD = PlayerController->GetHUD<ACountrySelectionHUD>();
	
		CountrySelectionHUD->GetSelectedCountryWidget()->SetCountry(Province->GetOwnerCountry());
		Pawn->GetGameInstance<UMyGameInstance>()->SetRuledCountry(PlayerController, Province->GetOwnerCountry());
	}
	
	return Instance;
}

TSharedPtr<FPawnState> FCountrySelectionPawnState::RightClick(APawn* ProvidedPawn)
{
	return Instance;
}

bool FCountrySelectionPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return true;
}

bool FCountrySelectionPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return true;
}

FCountrySelectionPawnState::FCountrySelectionPawnState()
{
}
