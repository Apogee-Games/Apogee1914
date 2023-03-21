#include "Widgets/Maps/MapsSwitcherWidget.h"

#include "Maps/MapsSwitcher.h"

void UMapsSwitcherWidget::NativeConstruct()
{
	Super::NativeConstruct();
	FlagsMapButton->OnClicked.AddDynamic(this, &UMapsSwitcherWidget::OnFlagsMapButtonClick);
	CountriesMapButton->OnClicked.AddDynamic(this, &UMapsSwitcherWidget::OnCountriesMapButtonClick);
	RelationsMapButton->OnClicked.AddDynamic(this, &UMapsSwitcherWidget::OnRelationsMapButtonClick);
	SelectionMapCheckBox->OnCheckStateChanged.AddDynamic(this, &UMapsSwitcherWidget::OnSelectionMapCheckBoxCheck);
	ProvinceOutlineMapCheckBox->OnCheckStateChanged.AddDynamic(this, &UMapsSwitcherWidget::OnProvinceOutlineMapCheckBoxCheck);
}

void UMapsSwitcherWidget::OnFlagsMapButtonClick()
{
	GetGameInstance()->GetSubsystem<UMapsSwitcher>()->SelectFlagsMap(GetOwningPlayerPawn<AHumanPlayerPawn>());
}

void UMapsSwitcherWidget::OnCountriesMapButtonClick()
{
	GetGameInstance()->GetSubsystem<UMapsSwitcher>()->SelectCountriesMap(GetOwningPlayerPawn<AHumanPlayerPawn>());
}

void UMapsSwitcherWidget::OnRelationsMapButtonClick()
{
	GetGameInstance()->GetSubsystem<UMapsSwitcher>()->SelectRelationMap(GetOwningPlayerPawn<AHumanPlayerPawn>());
}

void UMapsSwitcherWidget::OnSelectionMapCheckBoxCheck(bool Value)
{
	GetGameInstance()->GetSubsystem<UMapsSwitcher>()->SetApplySelectionMap(GetOwningPlayerPawn<AHumanPlayerPawn>(), Value);
}

void UMapsSwitcherWidget::OnProvinceOutlineMapCheckBoxCheck(bool Value)
{
	GetGameInstance()->GetSubsystem<UMapsSwitcher>()->SetApplyProvinceOutlineMap(GetOwningPlayerPawn<AHumanPlayerPawn>(), Value);
}
