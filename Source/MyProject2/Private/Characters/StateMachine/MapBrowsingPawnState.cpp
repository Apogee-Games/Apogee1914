#include "Characters/StateMachine/MapBrowsingPawnState.h"

#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Administration/Instances/State.h"
#include "Characters/HUDs/HumanPlayerHUD.h"
#include "Characters/StateMachine/CountryDiplomacyPawnState.h"
#include "Maps/Selection/SelectionMap.h"

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
	
	USelectionMap* SelectionMap = Pawn->GetWorld()->GetGameInstance()->GetSubsystem<USelectionMap>();

	UProvince* Province = SelectionMap->SelectProvince(Pawn->MapActor->GetMapPosition(Pawn));

	AHumanPlayerHUD* HUD = Pawn->GetController<APlayerController>()->GetHUD<AHumanPlayerHUD>();

	UProvinceDataWidget* ProvinceDataWidget = HUD->GetProvinceDataWidget();

	ProvinceDataWidget->SetNewProvince(Province);

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
