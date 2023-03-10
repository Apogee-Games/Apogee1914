#include "BuildingCreationPawnState.h"

#include "MapBrowsingPawnState.h"
#include "MyProject2/Characters/HumanPlayerPawn.h"
#include "MyProject2/Economics/Managers/Public/BuildingManager.h"
#include "MyProject2/Maps/Selection/SelectionMap.h"
#include "MyProject2/Utils/LocationUtils.h"
#include "MyProject2/Widgets/Economics/Buildings/Creation/BuildingsTypesListWidget.h"

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
	
	USelectionMap* SelectionMap = Pawn->GetWorld()->GetSubsystem<USelectionMap>();

	const FVector Point = FLocationUtils::GetNormalizedPositionOnPlane(Pawn);

	UProvince* Province = SelectionMap->SelectProvince(FVector2D(Point.Y, Point.Z));

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
