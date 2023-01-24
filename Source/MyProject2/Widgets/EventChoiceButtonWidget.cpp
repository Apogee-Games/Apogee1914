#include "EventChoiceButtonWidget.h"

void UEventChoiceButtonWidget::SetChoiceText(const FString& Text) const
{
	ChoiceTextBlock->SetText(FText::FromString(Text));
}

void UEventChoiceButtonWidget::OnChoiceButtonClick()
{
	EventManager->RegisterChoice(EventName, ChoiceName, CountryTag);
}

void UEventChoiceButtonWidget::Init(const FString& NewEventName, const FString& NewChoiceName, const FString& NewCountryTag, const FString& NewChoiceText, FEventManager* NewEventManager)
{
	EventName = NewEventName;
	ChoiceName = NewChoiceName;
	EventManager = NewEventManager;
	CountryTag = NewCountryTag;
	SetChoiceText(NewChoiceText);
	
	ChoiceButton->OnClicked.AddDynamic(this, &UEventChoiceButtonWidget::OnChoiceButtonClick);
}
