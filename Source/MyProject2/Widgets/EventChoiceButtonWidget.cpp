#include "EventChoiceButtonWidget.h"

#include "MyProject2/Events/EventInstancesController.h"

void UEventChoiceButtonWidget::SetChoiceText(const FString& Text) const
{
	ChoiceTextBlock->SetText(FText::FromString(Text));
}

void UEventChoiceButtonWidget::OnChoiceButtonClick()
{
	GetGameInstance()->GetSubsystem<UEventInstancesController>()->RegisterChoice(EventName, ChoiceName, CountryTag);
}

void UEventChoiceButtonWidget::Init(const FString& NewEventName, const FString& NewChoiceName, const FString& NewCountryTag, const FString& NewChoiceText)
{
	EventName = NewEventName;
	ChoiceName = NewChoiceName;
	CountryTag = NewCountryTag;
	SetChoiceText(NewChoiceText);
	
	ChoiceButton->OnClicked.AddDynamic(this, &UEventChoiceButtonWidget::OnChoiceButtonClick);
}
