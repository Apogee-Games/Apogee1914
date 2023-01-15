#include "EventChoiceButtonWidget.h"

void UEventChoiceButtonWidget::SetChoiceText(const FString& Text) const
{
	ChoiceTextBlock->SetText(FText::FromString(Text));
}

void UEventChoiceButtonWidget::OnChoiceButtonClick()
{
	EventManager->RegisterChoice(EventName, ChoiceName);
}

void UEventChoiceButtonWidget::Init(const FString& NewEventName, const FString& NewChoiceName, const FString& NewChoiceText, FEventManager* NewEventManager)
{
	EventName = NewEventName;
	ChoiceName = NewChoiceName;
	EventManager = NewEventManager;
	SetChoiceText(NewChoiceText);
	
	ChoiceButton->OnClicked.AddDynamic(this, &UEventChoiceButtonWidget::OnChoiceButtonClick);
}
