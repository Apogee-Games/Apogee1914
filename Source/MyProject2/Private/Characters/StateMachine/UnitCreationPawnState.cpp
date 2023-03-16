#include "Characters/StateMachine/UnitCreationPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Maps/Selection/SelectionMap.h"
#include "Characters/HumanPlayerPawn.h"
#include "Military/Managers/UnitsFactory.h"
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

	UProvince* Province = SelectionMap->SelectProvince(Pawn->MapActor->GetMapPosition(Pawn));

	UUnitsFactory* UnitsFactory = Pawn->GetWorld()->GetSubsystem<UUnitsFactory>();

	UnitsFactory->CreateUnit(Pawn->GetSelectedUnitDescription(), Province, Pawn->GetRuledCountryTag());
	// TODO: Add method overload to be able to pass country not just its tag

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

