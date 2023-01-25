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
	void SetChoiceText(const FString& Text) const;

	/**
	 *	Method used to initialize widget
	 *	Sets all necessary data to be able to report selected choice back to event manager
	 */
	void Init(const FString& NewEventName, const FString& NewChoiceName, const FString& NewCountryTag, const FString& NewChoiceText);
	
private:
	FString EventName;

	FString ChoiceName;

	FString CountryTag;

	UFUNCTION()
	void OnChoiceButtonClick();
};
