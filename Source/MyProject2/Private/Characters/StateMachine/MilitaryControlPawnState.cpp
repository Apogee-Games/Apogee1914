#include "Characters/StateMachine/MilitaryControlPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Maps/Selection/SelectionMap.h"
#include "Military/Managers/UnitsMover.h"
#include "Widgets/Military/Selection/UnitInstancesListDescriptionWidget.h"

TSharedPtr<FPawnState> FMilitaryControlPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FMilitaryControlPawnState>(new FMilitaryControlPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FMilitaryControlPawnState::LeftClick(AHumanPlayerPawn* Pawn)
{
	Pawn->UnitSelectionComponent->ClearSelectedUnits();
	return FMapBrowsingPawnState::GetInstance()->LeftClick(Pawn);
}

TSharedPtr<FPawnState> FMilitaryControlPawnState::RightClick(AHumanPlayerPawn* Pawn)
{
	FVector2d Point = Pawn->MapActor->GetMapPosition(Pawn);

	UProvince* To = Pawn->GetWorld()->GetGameInstance()->GetSubsystem<USelectionMap>()->GetProvince(Point);

	UUnitsMover* UnitsMover = Pawn->GetWorld()->GetSubsystem<UUnitsMover>();
	
	for (const auto& Unit: Pawn->UnitSelectionComponent->GetSelectedUnits())
	{
		UnitsMover->MoveUnit(Unit, To);
	}
	
	return Instance;
}

bool FMilitaryControlPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UUnitInstancesListDescriptionWidget*>(Widget) != nullptr;
}

bool FMilitaryControlPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FMilitaryControlPawnState::FMilitaryControlPawnState()
{
}
