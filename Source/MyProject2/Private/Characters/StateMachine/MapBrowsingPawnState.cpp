#include "Characters/StateMachine/MapBrowsingPawnState.h"

#include "MyProject2GameModeBase.h"
#include "Characters/HumanPlayerPawn.h"

#include "Administration/Instances/State.h"
#include "Characters/HumanPlayerHUD.h"
#include "Characters/MyPlayerController.h"
#include "Maps/Selection/SelectionMap.h"
#include "Utils/LocationUtils.h"

TSharedPtr<FPawnState> FMapBrowsingPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FMapBrowsingPawnState>(new FMapBrowsingPawnState);
	}
	return Instance;
}

TSharedPtr<FPawnState> FMapBrowsingPawnState::LeftClick(AHumanPlayerPawn* Pawn)
{
	USelectionMap* SelectionMap = Pawn->GetWorld()->GetSubsystem<USelectionMap>();

	const FVector Point = FLocationUtils::GetNormalizedPositionOnPlane(Pawn);

	UProvince* Province = SelectionMap->SelectProvince(FVector2D(Point.Y, Point.Z));

	AHumanPlayerHUD* HUD = Pawn->GetController<AMyPlayerController>()->GetHUD<AHumanPlayerHUD>();

	UProvinceDataWidget* ProvinceDataWidget = HUD->GetProvinceDataWidget();

	ProvinceDataWidget->SetNewProvince(Province);

	Pawn->UnitSelectionComponent->ClearSelectedUnits();
	
	return Instance;
}

TSharedPtr<FPawnState> FMapBrowsingPawnState::RightClick(AHumanPlayerPawn* Pawn)
{
	return Instance;
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
