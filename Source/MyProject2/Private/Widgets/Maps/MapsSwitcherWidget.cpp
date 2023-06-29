#include "Widgets/Maps/MapsSwitcherWidget.h"

#include "Maps/MapController.h"

void UMapsSwitcherWidget::NativeConstruct()
{
	Super::NativeConstruct();
	FlagsMapButton->OnClicked.AddDynamic(this, &UMapsSwitcherWidget::OnFlagsMapButtonClick);
	CountriesMapButton->OnClicked.AddDynamic(this, &UMapsSwitcherWidget::OnCountriesMapButtonClick);
	RelationsMapButton->OnClicked.AddDynamic(this, &UMapsSwitcherWidget::OnRelationsMapButtonClick);
	AlliancesMapButton->OnClicked.AddDynamic(this, &UMapsSwitcherWidget::OnAlliancesMapButton);
	IdeologyMapButton->OnClicked.AddDynamic(this, &UMapsSwitcherWidget::OnIdeologyMapButtonClick);
	ProvinceOutlineMapCheckBox->OnCheckStateChanged.AddDynamic(this, &UMapsSwitcherWidget::OnProvinceOutlineMapCheckBoxCheck);
}

void UMapsSwitcherWidget::OnFlagsMapButtonClick()
{
	//GetGameInstance()->GetSubsystem<UMapController>()->SelectFlagsMap(GetOwningPlayerPawn<AHumanPlayerPawn>());
}

void UMapsSwitcherWidget::OnCountriesMapButtonClick()
{
	GetGameInstance()->GetSubsystem<UMapController>()->SetCountriesMapAll();
}

void UMapsSwitcherWidget::OnRelationsMapButtonClick()
{
	GetGameInstance()->GetSubsystem<UMapController>()->SetCountryRelationMapAll();
}

void UMapsSwitcherWidget::OnAlliancesMapButton()
{
	GetGameInstance()->GetSubsystem<UMapController>()->SetAlliancesMapAll();
}

void UMapsSwitcherWidget::OnIdeologyMapButtonClick()
{
	GetGameInstance()->GetSubsystem<UMapController>()->SetIdeologiesMapAll();
}

void UMapsSwitcherWidget::OnProvinceOutlineMapCheckBoxCheck(bool Value)
{
	GetGameInstance()->GetSubsystem<UMapController>()->SetOutlineEnabled(Value);
}
