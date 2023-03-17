#include "Characters/StateMachine/BuildingCreationPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Economics/Managers/BuildingManager.h"
#include "Maps/Selection/SelectionMap.h"
#include "Widgets/Economics/Buildings/Creation/BuildingsTypesListWidget.h"

TSharedPtr<FPawnState> FBuildingCreationPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FBuildingCreationPawnState>(new FBuildingCreationPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FBuildingCreationPawnState::LeftClick(AHumanPlayerPawn* Pawn)
{
	if (!Pawn->GetSelectedBuildingDescription()) return Instance;
	
	USelectionMap* SelectionMap = Pawn->GetWorld()->GetGameInstance()->GetSubsystem<USelectionMap>();

	UProvince* Province = SelectionMap->SelectProvince(Pawn->MapActor->GetMapPosition(Pawn));

	UBuildingManager* BuildingManager = Pawn->GetWorld()->GetSubsystem<UBuildingManager>();

	BuildingManager->BuildBuilding(Pawn->GetSelectedBuildingDescription(), Province, Pawn->GetRuledCountry()->GetStorage());

	return Instance;
}

TSharedPtr<FPawnState> FBuildingCreationPawnState::RightClick(AHumanPlayerPawn* Pawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(Pawn);
}

bool FBuildingCreationPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UBuildingsTypesListWidget*>(Widget) != nullptr;
}

bool FBuildingCreationPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return false;
}

FBuildingCreationPawnState::FBuildingCreationPawnState()
{
}
