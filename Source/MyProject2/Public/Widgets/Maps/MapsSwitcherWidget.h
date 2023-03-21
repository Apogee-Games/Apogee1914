#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"

#include "MapsSwitcherWidget.generated.h"

UCLASS()
class UMapsSwitcherWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* FlagsMapButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* CountriesMapButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* RelationsMapButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UCheckBox* SelectionMapCheckBox;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UCheckBox* ProvinceOutlineMapCheckBox;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnFlagsMapButtonClick();

	UFUNCTION()
	void OnCountriesMapButtonClick();

	UFUNCTION()
	void OnRelationsMapButtonClick();

	UFUNCTION()
	void OnSelectionMapCheckBoxCheck(bool Value);

	UFUNCTION()
	void OnProvinceOutlineMapCheckBoxCheck(bool Value);
};
