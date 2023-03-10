#include "Characters/StateMachine/UnitCreationPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Maps/Selection/SelectionMap.h"
#include "Characters/HumanPlayerPawn.h"
#include "Military/Managers/UnitsFactory.h"
#include "Utils/LocationUtils.h"
#include "Widgets/Military/Creation/UnitTypesListWidget.h"


TSharedPtr<FPawnState> FUnitCreationPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FUnitCreationPawnState>(new FUnitCreationPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FUnitCreationPawnState::LeftClick(AHumanPlayerPawn* Pawn)
{
	if (!Pawn->GetSelectedUnitDescription()) return Instance;
	
	USelectionMap* SelectionMap = Pawn->GetWorld()->GetSubsystem<USelectionMap>();

	const FVector Point = FLocationUtils::GetNormalizedPositionOnPlane(Pawn);

	UProvince* Province = SelectionMap->SelectProvince(FVector2D(Point.Y, Point.Z));

	UUnitsFactory* UnitsFactory = Pawn->GetWorld()->GetSubsystem<UUnitsFactory>();

	UnitsFactory->Create(Pawn->GetSelectedUnitDescription(), Province, Pawn->GetRuledCountryTag());

	return Instance;
}

TSharedPtr<FPawnState> FUnitCreationPawnState::RightClick(AHumanPlayerPawn* Pawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(Pawn);	
}

bool FUnitCreationPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UUnitTypesListWidget*>(Widget) != nullptr;
}

bool FUnitCreationPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return MustWidgetBeVisible(Widget);
}

FUnitCreationPawnState::FUnitCreationPawnState()
{
}

