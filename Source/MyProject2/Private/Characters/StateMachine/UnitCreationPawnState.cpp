#include "Characters/StateMachine/UnitCreationPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Maps/Selection/SelectionMap.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
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

TSharedPtr<FPawnState> FUnitCreationPawnState::LeftClick(APawn* ProvidedPawn)
{
	AHumanPlayerPawn* Pawn = Cast<AHumanPlayerPawn>(ProvidedPawn);
	
	if (!Pawn->GetSelectedUnitDescription()) return Instance;
	
	USelectionMap* SelectionMap = Pawn->GetWorld()->GetGameInstance()->GetSubsystem<USelectionMap>();

	UProvince* Province = SelectionMap->SelectProvince(Pawn->MapActor->GetMapPosition(Pawn));

	if (Pawn->GetRuledCountry() != Province->GetOwnerCountry()) return Instance;

	UUnitsFactory* UnitsFactory = Pawn->GetWorld()->GetSubsystem<UUnitsFactory>();

	UnitsFactory->CreateUnit(Pawn->GetSelectedUnitDescription(), Province, Pawn->GetRuledCountryTag());
	// TODO: Add method overload to be able to pass country not just its tag

	return Instance;
}

TSharedPtr<FPawnState> FUnitCreationPawnState::RightClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(ProvidedPawn);	
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

