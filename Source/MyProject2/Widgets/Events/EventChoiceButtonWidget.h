#pragma once
#include "EventChoiceCarrier.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "EventChoiceButtonWidget.generated.h"

/**
 * Widget for event choice button
 */
UCLASS()
class MYPROJECT2_API UEventChoiceButtonWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* ChoiceButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* ChoiceTextBlock;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetCarrier(UObject* ProvidedCarrier);

	UFUNCTION(BlueprintCallable)
	void RefreshData();
private:
	UPROPERTY()
	UEventChoiceCarrier* Carrier;
	
	UFUNCTION()
	void OnChoiceButtonClick();
};
