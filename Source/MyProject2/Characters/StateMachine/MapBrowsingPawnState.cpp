#include "MapBrowsingPawnState.h"

#include "MyProject2/MyProject2GameModeBase.h"
#include "MyProject2/Characters/HumanPlayerPawn.h"

#include "MyProject2/Administration/Instances/State.h"
#include "MyProject2/Administration/Managers/StateManager.h"
#include "MyProject2/Characters/HumanPlayerHUD.h"
#include "MyProject2/Characters/MyPlayerController.h"
#include "MyProject2/Maps/Selection/SelectionMap.h"
#include "MyProject2/Utils/LocationUtils.h"

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

	Pawn->ClearSelectedUnits();
	
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
