// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Maps/MapController.h"
#include "MapModeItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UMapModeItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TMap<EMapMode, UTexture2D*> MapModesIcons;
	
	UPROPERTY(EditAnywhere)
	TMap<EMapMode, FString> MapModesNames;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* MapModeIcon;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* MapModeName;

	void SetMapMode(EMapMode MapMode);

	void SetIsContentMode(bool bIsContentMode);
};
