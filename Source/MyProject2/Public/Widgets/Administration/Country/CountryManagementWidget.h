#pragma once
#include "ParliamentWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "CountryManagementWidget.generated.h"

UCLASS()
class UCountryManagementWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UParliamentWidget* FirstChamberParliamentWidget;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UWidgetSwitcher* FirstChamberParliamentWidgetSwitcher;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UParliamentWidget* SecondChamberParliamentWidget;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UWidgetSwitcher* SecondChamberParliamentWidgetSwitcher;


	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* RulerImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
 	UTextBlock* RulerNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* IdeologyNameTextBlock;
	
	virtual void NativeConstruct() override;
};
