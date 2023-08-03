// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Maps/MapModeItemWidget.h"

void UMapModeItemWidget::SetMapMode(EMapMode MapMode)
{
	if (MapModesIcons.Contains(MapMode)) {
		MapModeIcon->SetBrushResourceObject(MapModesIcons[MapMode]);
	}
	else
	{
		MapModeIcon->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	}

	if (MapModesNames.Contains(MapMode))
	{
		MapModeName->SetText(FText::FromString(MapModesNames[MapMode]));
	}
}

void UMapModeItemWidget::SetIsContentMode(bool bIsContentMode)
{
	if (bIsContentMode)
	{
		MapModeName->SetVisibility(ESlateVisibility::Collapsed);	
	}
	else
	{
		MapModeName->SetVisibility(ESlateVisibility::Visible);	
	}
}
