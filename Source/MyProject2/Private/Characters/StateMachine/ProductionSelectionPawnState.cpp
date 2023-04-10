#include "Characters/StateMachine/ProductionSelectionPawnState.h"

#include "Characters/StateMachine/MapBrowsingPawnState.h"
#include "Widgets/Economics/Buildings/Production/ProducibleGoodsListWidget.h"
#include "Widgets/Economics/Buildings/Production/ProductionListWidget.h"


TSharedPtr<FPawnState> FProductionSelectionPawnState::GetInstance()
{
	if (!Instance)
	{
		Instance = TSharedPtr<FProductionSelectionPawnState>(new FProductionSelectionPawnState);
	}
	return Instance;
}


TSharedPtr<FPawnState> FProductionSelectionPawnState::LeftClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->LeftClick(ProvidedPawn);
}

TSharedPtr<FPawnState> FProductionSelectionPawnState::RightClick(APawn* ProvidedPawn)
{
	return FMapBrowsingPawnState::GetInstance()->RightClick(ProvidedPawn);
}

bool FProductionSelectionPawnState::MustWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UProducibleGoodsListWidget*>(Widget) != nullptr;
}

bool FProductionSelectionPawnState::CanWidgetBeVisible(UUserWidget* Widget)
{
	return dynamic_cast<UProductionListWidget*>(Widget) != nullptr;
}

FProductionSelectionPawnState::FProductionSelectionPawnState()
{
}
