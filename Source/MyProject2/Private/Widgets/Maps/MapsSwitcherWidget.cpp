#include "Widgets/Maps/MapsSwitcherWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Maps/MapController.h"
#include "Widgets/Maps/MapModeComboBox.h"
#include "Widgets/Maps/MapModeItemWidget.h"

void UMapsSwitcherWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MapController = GetGameInstance()->GetSubsystem<UMapController>();
	TArray<EMapMode>& MapItems = MapController->GetMapItems();
	
	CreateWidgets();
	CreateComboBoxes(MapItems);
	RefreshOptions(MapItems);
}

UWidget* UMapsSwitcherWidget::OnCreateContentWidget(EMapMode Item)
{
	if (Item == EMapMode::None)
	{
		return NoneMapModeContentWidget;
	}
	
	UMapModeItemWidget* Widget = Widgets[Item];
	Widget->SetIsContentMode(true);
	return Widget;
}

UWidget* UMapsSwitcherWidget::OnCreateItemWidget(EMapMode Item)
{
	UMapModeItemWidget* Widget = Widgets[Item];
	Widget->SetIsContentMode(false);
	return Widget;
}

void UMapsSwitcherWidget::OnItemSelected(EMapMode SelectedItem, ESelectInfo::Type SelectionType)
{
	TArray<EMapMode>& MapItems = MapController->GetMapItems();

	int32 Index = INDEX_NONE;

	for (int32 i = 0; i < MapItems.Num(); ++i)
	{
		if (ComboBoxes[i]->GetSelectedOption() != MapItems[i])
		{
			Index = i;
			break;
		}
	}

	if (Index != INDEX_NONE)
	{
		MapItems[Index] = SelectedItem;
		
		RefreshOptions(MapItems);
	}
}

void UMapsSwitcherWidget::OnMapModeSelected(EMapMode MapMode)
{
	MapController->SetMapMode(MapMode);
}

void UMapsSwitcherWidget::CreateWidgets()
{
	for (EMapMode MapMode: TEnumRange<EMapMode>())
	{
		UMapModeItemWidget* Widget = WidgetTree->ConstructWidget<UMapModeItemWidget>(MapModeItemWidgetClass);
		Widget->SetMapMode(MapMode);
		Widgets.Add(MapMode, Widget);
	}

	NoneMapModeContentWidget = WidgetTree->ConstructWidget<UMapModeItemWidget>(MapModeItemWidgetClass);
	NoneMapModeContentWidget->SetMapMode(EMapMode::None);
	NoneMapModeContentWidget->SetIsContentMode(true);
}

void UMapsSwitcherWidget::CreateComboBoxes(const TArray<EMapMode>& MapItems)
{
	for (int32 i = 0; i < MapItems.Num(); ++i)
	{
		UMapModeComboBox* ComboBox = WidgetTree->ConstructWidget<UMapModeComboBox>(MapModeComboBoxClass);

		ComboBox->OnLeftMouseClick.BindDynamic(this, &ThisClass::OnMapModeSelected);
		ComboBox->OnGenerateContentWidget.BindDynamic(this, &ThisClass::OnCreateContentWidget);
		ComboBox->OnGenerateItemWidget.BindDynamic(this, &ThisClass::OnCreateItemWidget);
		ComboBox->OnSelectionChanged.AddDynamic(this, &ThisClass::OnItemSelected);

		ComboBox->AddOption(EMapMode::None);
		ComboBox->SetSelectedOption(EMapMode::None);
		
		MapOptions->AddChildToHorizontalBox(ComboBox);
		ComboBoxes.Add(ComboBox);
	}
}

void UMapsSwitcherWidget::RefreshOptions(const TArray<EMapMode>& MapItems)
{
	TSet<EMapMode> TakenMapModes;
	for (EMapMode MapMode: MapItems)
	{
		if (MapMode != EMapMode::None)
		{
			TakenMapModes.Add(MapMode);
		}
	}

	TArray<EMapMode> Options;
	for (EMapMode MapMode: TEnumRange<EMapMode>())
	{
		if (!TakenMapModes.Contains(MapMode))
		{
			Options.Add(MapMode);
		}
	}

	for (int32 i = 0; i < MapItems.Num(); ++i)
	{
		UMapModeComboBox* ComboBoxKey = ComboBoxes[i];

		ComboBoxKey->OnSelectionChanged.RemoveAll(this);

		ComboBoxKey->ClearOptions();

		for (EMapMode Option: Options)
		{
			ComboBoxKey->AddOption(Option);
		}

		ComboBoxKey->SetSelectedOption(MapItems[i]);

		ComboBoxKey->OnSelectionChanged.AddDynamic(this, &ThisClass::OnItemSelected);
	}
}