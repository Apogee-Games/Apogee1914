#pragma once
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InvitationalCountryWidget.generated.h"

UCLASS()
class UInvitationalCountryWidget: public UUserWidget
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
	virtual void NativeDestruct() override;

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
