#pragma once
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

	//TODO: Add logic for disabling play button if a player haven't selected country
	//TODO: Probably make button ready to play which will be accessible after everyone have pressed it :)
private:
	UFUNCTION()
	void OnPlayButtonClick();

	UFUNCTION()
	void OnBackButtonClick();
};
