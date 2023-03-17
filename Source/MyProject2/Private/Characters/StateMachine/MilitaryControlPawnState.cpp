#include "Characters/StateMachine/MilitaryControlPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Maps/Selection/SelectionMap.h"
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
	
	FVector2d Point = Pawn->MapActor->GetMapPosition(Pawn);

	UProvince* To = Pawn->GetWorld()->GetGameInstance()->GetSubsystem<USelectionMap>()->GetProvince(Point);

	UUnitsMover* UnitsMover = Pawn->GetWorld()->GetSubsystem<UUnitsMover>();

	UnitsMover->MoveUnits(Pawn->UnitSelectionComponent->GetSelectedUnits(), To);
	UnitsMover->MoveUnits(Pawn->UnitSelectionComponent->GetSelectedUnitsCollections(), To);
	UnitsMover->MoveUnits(Pawn->UnitSelectionComponent->GetSelectedUnitsCollectionGroups(), To);
	
	for (const auto& UnitsCollectionGroup: Pawn->UnitSelectionComponent->GetSelectedUnitsCollectionGroups())
	{
		for (const auto& UnitsCollection: UnitsCollectionGroup->GetAll())
		{
			for (const auto& Unit: UnitsCollection->GetAll())
			{
				UnitsMover->MoveUnit(Unit, To);
			}
		}
	}

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
