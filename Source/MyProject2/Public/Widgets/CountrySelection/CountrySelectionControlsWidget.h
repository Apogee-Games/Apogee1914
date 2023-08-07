#pragma once
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CountrySelectionControlsWidget.generated.h"

UCLASS()
class UCountrySelectionControlsWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* PlayButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* BackButton;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UFUNCTION()
	void OnPlayButtonClick();

	UFUNCTION()
	void OnBackButtonClick();

	UFUNCTION()
	void CountryWasSelected(int32 PlayerId, UCountry* Country);
	
	//TODO: Probably make button ready to play which will be accessible after everyone have pressed it :)
};
