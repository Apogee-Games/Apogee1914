#include "EventChoiceButtonWidget.h"

#include "MyProject2/Events/EventInstancesController.h"

void UEventChoiceButtonWidget::SetChoiceText(const FText& Text) const
{
	ChoiceTextBlock->SetText(Text);
}

void UEventChoiceButtonWidget::OnChoiceButtonClick()
{
	GetWorld()->GetSubsystem<UEventInstancesController>()->RegisterChoice(EventName, ChoiceName, CountryTag);
}

void UEventChoiceButtonWidget::Init(const FName& NewEventName, const FName& NewChoiceName, const FName& NewCountryTag, const FText& NewChoiceText)
{
	EventName = NewEventName;
	ChoiceName = NewChoiceName;
	CountryTag = NewCountryTag;
	SetChoiceText(NewChoiceText);
	
	ChoiceButton->OnClicked.AddDynamic(this, &UEventChoiceButtonWidget::OnChoiceButtonClick);
}
