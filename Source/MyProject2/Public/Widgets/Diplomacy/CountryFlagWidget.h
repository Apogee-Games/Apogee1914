#pragma once
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "CountryFlagWidget.generated.h"
UCLASS()
class UCountryFlagWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* CountryFlagImage;

	UFUNCTION(BlueprintCallable)
	void SetCountry(UObject* ProvidedCountry);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UCountry* Country;
};
