#include "Characters/StateMachine/CountrySelectionPawnState.h"

#include "MyGameInstance.h"
#include "Characters/HUDs/CountrySelectionHUD.h"
#include "Characters/Pawns/CountrySelectionPawn.h"
#include "Maps/Selection/SelectionMap.h"

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
	
	USelectionMap* SelectionMap = ProvidedPawn->GetGameInstance()->GetSubsystem<USelectionMap>();

	FVector2d Point = Pawn->MapActor->GetMapPosition(Pawn);
	
	UProvince* Province = SelectionMap->GetProvince(Point);

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
