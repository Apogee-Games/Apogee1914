#include "MilitaryControlPawnState.h"

#include "MapBrowsingPawnState.h"
#include "MyProject2/Characters/HumanPlayerPawn.h"
#include "MyProject2/Maps/Selection/SelectionMap.h"
#include "MyProject2/Military/Managers/UnitsMover.h"
#include "MyProject2/Utils/LocationUtils.h"

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
	Pawn->ClearSelectedUnits();
	return FMapBrowsingPawnState::GetInstance()->LeftClick(Pawn);
}

TSharedPtr<FPawnState> FMilitaryControlPawnState::RightClick(AHumanPlayerPawn* Pawn)
{
	const FVector Point = FLocationUtils::GetNormalizedPositionOnPlane(Pawn);

	UProvince* To = Pawn->GetWorld()->GetSubsystem<USelectionMap>()->GetProvince(FVector2D(Point.Y, Point.Z));

	UUnitsMover* UnitsMover = Pawn->GetWorld()->GetSubsystem<UUnitsMover>();
	
	for (const auto& Unit: Pawn->GetSelectedUnits())
	{
		UnitsMover->MoveUnit(Unit, To);
	}
	
	return Instance;
}

bool FMilitaryControlPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

bool FMilitaryControlPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FMilitaryControlPawnState::FMilitaryControlPawnState()
{
}
