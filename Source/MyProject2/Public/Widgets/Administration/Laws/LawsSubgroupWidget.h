﻿#pragma once
#include "LawButtonWidget.h"
#include "Administration/Descriptions/LawDescription.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "LawsSubgroupWidget.generated.h"

UCLASS()
class ULawsSubgroupWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UScrollBox* LawsButtonsScrollBox;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* SubgroupNameTextBlock;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ULawButtonWidget> LawButtonWidgetClass; 

	void Init(ULawDescriptionWidget* ProvidedLawDescriptionWidget, const FName& SubgroupName);

	void AddLaw(FLawDescription* LawDescription);
private:
	UPROPERTY()
	ULawDescriptionWidget* LawDescriptionWidget;
};
