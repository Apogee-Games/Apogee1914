#pragma once
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

	/**
	 * Method used to set choice text
	 */
	void SetChoiceText(const FText& Text) const;

	/**
	 *	Method used to initialize widget
	 *	Sets all necessary data to be able to report selected choice back to event manager
	 */
	void Init(const FName& NewEventName, const FName& NewChoiceName, const FName& NewCountryTag, const FText& NewChoiceText);
	
private:
	FName EventName;

	FName ChoiceName;

	FName CountryTag;

	UFUNCTION()
	void OnChoiceButtonClick();
};
