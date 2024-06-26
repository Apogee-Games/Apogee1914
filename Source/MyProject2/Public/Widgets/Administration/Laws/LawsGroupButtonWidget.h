﻿#pragma once
#include "Administration/Descriptions/Law/LawsGroup.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "LawsGroupButtonWidget.generated.h"

UCLASS()
class ULawsGroupButtonWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* GroupButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* GroupTextBlock;
	
	void Init(ULawsGroup* LawsGroup, UWidgetSwitcher* ProvidedWidgetSwitcher, int32 ProvidedIndex);
private:
	UPROPERTY()
	UWidgetSwitcher* WidgetSwitcher;

	int32 Index;

	UFUNCTION()
	void OnButtonClick();
};
