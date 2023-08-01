#include "Widgets/TopPanelWidget.h"

#include "Administration/Instances/Country.h"
#include "Characters/Pawns/HumanPlayerPawn.h"
#include "Characters/StateMachine/BuildingCreationPawnState.h"
#include "Characters/StateMachine/CountryManagementPawnState.h"
#include "Characters/StateMachine/LawsBrowsingPawnState.h"
#include "Characters/StateMachine/ProductionBrowsingPawnState.h"
#include "Characters/StateMachine/StorageBrowsingPawnState.h"
#include "Characters/StateMachine/SupplyBrowsingPawnState.h"
#include "Characters/StateMachine/UnitCreationPawnState.h"

void UTopPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UnitCreationButton->OnClicked.AddDynamic(this, &UTopPanelWidget::OnUnitCreationButtonClick);
	StorageBrowsingButton->OnClicked.AddDynamic(this, &UTopPanelWidget::OnStorageBrowsingButtonClick);
	SupplyBrowsingButton->OnClicked.AddDynamic(this, &UTopPanelWidget::OnSupplyBrowsingButton);
	BuildingCreationButton->OnClicked.AddDynamic(this, &UTopPanelWidget::OnBuildingCreationButtonClick);
	CountryFlagButton->OnClicked.AddDynamic(this, &UTopPanelWidget::OnCountryFlagButtonClick);
	LawsBrowsingButton->OnClicked.AddDynamic(this, &UTopPanelWidget::OnLawsBrowsingButtonClick);
	ProductionBrowsingButton->OnClicked.AddDynamic(this, &UTopPanelWidget::OnProductionBrowsingButtonClick);

	UCountry* Country = GetOwningPlayerPawn<AHumanPlayerPawn>()->GetRuledCountry();
	CountryFlagImage->SetBrushResourceObject(Country->GetFlag());
	ManpowerTextBlock->SetText(FText::FromString(TEXT("100k")));
	BuildingsNumberTextBlock->SetText(FText::FromString(TEXT("10")));
}

void UTopPanelWidget::OnUnitCreationButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchState<FUnitCreationPawnState>();
}

void UTopPanelWidget::OnStorageBrowsingButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchState<FStorageBrowsingPawnState>();
}

void UTopPanelWidget::OnSupplyBrowsingButton()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchState<FSupplyBrowsingPawnState>();
}

void UTopPanelWidget::OnBuildingCreationButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchState<FBuildingCreationPawnState>();
}

void UTopPanelWidget::OnCountryFlagButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchState<FCountryManagementPawnState>();
}

void UTopPanelWidget::OnLawsBrowsingButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchState<FLawsBrowsingPawnState>();
}

void UTopPanelWidget::OnProductionBrowsingButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchState<FProductionBrowsingPawnState>();
}
