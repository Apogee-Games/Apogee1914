#include "Widgets/TopPanelWidget.h"
#include "Characters/Pawns/HumanPlayerPawn.h"

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
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchUnitCreationState();
}

void UTopPanelWidget::OnStorageBrowsingButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchStorageBrowsingState();
}

void UTopPanelWidget::OnSupplyBrowsingButton()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchSupplyBrowsingState();
}

void UTopPanelWidget::OnBuildingCreationButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchBuildingCreationState();
}

void UTopPanelWidget::OnCountryFlagButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchCountryManagementState();
}

void UTopPanelWidget::OnLawsBrowsingButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchLawsBrowsingState();
}

void UTopPanelWidget::OnProductionBrowsingButtonClick()
{
	GetOwningPlayerPawn<AHumanPlayerPawn>()->SwitchProductionBrowsingState();
}
