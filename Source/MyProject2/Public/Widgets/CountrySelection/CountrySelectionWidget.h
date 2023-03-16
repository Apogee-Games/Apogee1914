#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "CountrySelectionWidget.generated.h"

UCLASS()
class UCountrySelectionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UEditableTextBox* CountryTagTextBox;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* SaveButton;

	virtual void NativeConstruct() override;
private:
	UFUNCTION()
	void OnSaveButtonClick();
};
