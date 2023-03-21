#pragma once
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ToBeInvitedCountryWidget.generated.h"

UCLASS()
class UToBeInvitedCountryWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* CountryFlag;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CountryNameTextBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetCountry(UObject* ProvidedCountry);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UCountry* Country;
	
	UFUNCTION()
	void OnButtonClick();
};
