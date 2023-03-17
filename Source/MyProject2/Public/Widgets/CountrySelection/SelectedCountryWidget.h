#pragma once
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SelectedCountryWidget.generated.h"

UCLASS()
class USelectedCountryWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* CountryFlagImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CountryNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* RulingFractionNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* RulerImage;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* RulerNameTextBlock;

	void SetCountry(UCountry* Country);
};
