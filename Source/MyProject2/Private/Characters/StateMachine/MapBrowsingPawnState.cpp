#include "Characters/StateMachine/MapBrowsingPawnState.h"

#include "Characters/HumanPlayerPawn.h"
#include "Administration/Instances/State.h"
#include "Characters/HumanPlayerHUD.h"
#include "Maps/Selection/SelectionMap.h"

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

	UProvince* Province = SelectionMap->SelectProvince(Pawn->MapActor->GetMapPosition(Pawn));

	AHumanPlayerHUD* HUD = Pawn->GetController<APlayerController>()->GetHUD<AHumanPlayerHUD>();

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
