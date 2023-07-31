#include "Widgets/Maps/MapsSwitcherWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/ComboBox.h"
#include "Components/ComboBoxKey.h"
#include "Components/ComboBoxString.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Framework/Styling/ComboButtonWidgetStyle.h"
#include "Kismet/KismetStringLibrary.h"
#include "Maps/MapController.h"

void UMapsSwitcherWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 0; i < 5; ++i)
	{
		UComboBoxKey* ComboBox = WidgetTree->ConstructWidget<UComboBoxKey>();
		for (const auto& MapMode: TEnumRange<EMapMode>())
		{
			if (MapModesNames.Contains(MapMode)) {
				ComboBox->AddOption(FName(MapModesNames[MapMode]));
			}
		}
		
		ComboBox->OnGenerateContentWidget.BindDynamic(this, &ThisClass::CreateContentWidget);
		ComboBox->OnGenerateItemWidget.BindDynamic(this, &ThisClass::CreateItemWidget);
		MapOptions->AddChildToHorizontalBox(ComboBox);
	}
}

UWidget* UMapsSwitcherWidget::CreateContentWidget(FName Item)
{
	for (EMapMode MapMode : TEnumRange<EMapMode>())
	{
		if (FName(MapModesNames[MapMode]) == Item)
		{
			UImage* Image = WidgetTree->ConstructWidget<UImage>();
			Image->SetBrushResourceObject(MapModesIcons[MapMode]);
			return Image;
		}
	}
	
	return nullptr;
}

UWidget* UMapsSwitcherWidget::CreateItemWidget(FName Item)
{
	for (EMapMode MapMode : TEnumRange<EMapMode>())
	{
		if (FName(MapModesNames[MapMode]) == Item)
		{
			UImage* Image = WidgetTree->ConstructWidget<UImage>();
			Image->SetBrushResourceObject(MapModesIcons[MapMode]);
			return Image;
		}
	}
	
	return nullptr;
}

/*
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
}*/
