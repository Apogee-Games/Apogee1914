#include "Characters/StateMachine/MilitaryControlPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Maps/MapController.h"
#include "Military/Managers/UnitsMover.h"
#include "Widgets/Military/Selection/SelectedUnitsListWidget.h"

TSharedPtr<FPawnState> FMilitaryControlPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FMilitaryControlPawnState>(new FMilitaryControlPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FMilitaryControlPawnState::LeftClick(APawn* ProvidedPawn)
{
	Cast<AHumanPlayerPawn>(ProvidedPawn)->UnitSelectionComponent->ClearSelectedUnits();
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

TSharedPtr<FPawnState> FMilitaryControlPawnState::RightClick(APawn* ProvidedPawn)
{
	AHumanPlayerPawn* Pawn = Cast<AHumanPlayerPawn>(ProvidedPawn);

	if (!Pawn->UnitSelectionComponent->HasSelectedUnits())
	{
		return FMapBrowsingPawnState::GetInstance()->RightClick(ProvidedPawn);
	}
	
	FVector2d Point = Pawn->MapActor->GetMapPosition(Pawn);

	UProvince* To = Pawn->GetGameInstance()->GetSubsystem<UMapController>()->SelectProvince(Point);

	UUnitsMover* UnitsMover = Pawn->GetGameInstance()->GetSubsystem<UUnitsMover>();

	UnitsMover->MoveUnits(Pawn->UnitSelectionComponent->GetUnitsSelectionsByBranch(), To);

	return Instance;
}

bool FMilitaryControlPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<USelectedUnitsListWidget*>(Widget) != nullptr;
}

bool FMilitaryControlPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FMilitaryControlPawnState::FMilitaryControlPawnState()
{
}
