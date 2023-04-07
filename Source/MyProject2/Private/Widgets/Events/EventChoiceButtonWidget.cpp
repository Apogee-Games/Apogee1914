
#include "Widgets/Events/EventChoiceButtonWidget.h"

#include "Events/EventInstancesController.h"

void UEventChoiceButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ChoiceButton->OnClicked.AddDynamic(this, &UEventChoiceButtonWidget::OnChoiceButtonClick);
}

void UEventChoiceButtonWidget::SetCarrier(UObject* ProvidedCarrier)
{
	Carrier = Cast<UEventChoiceCarrier>(ProvidedCarrier);
}

void UEventChoiceButtonWidget::RefreshData()
{
	ChoiceTextBlock->SetText(Carrier->GetChoiceText());
	ChoiceButton->SetIsEnabled(Carrier->IsChoiceActive());
}

void UEventChoiceButtonWidget::OnChoiceButtonClick()
{
	GetGameInstance()->GetSubsystem<UEventInstancesController>()->RegisterChoice(Carrier->GetEventDescription(), Carrier->GetChoiceName(), Carrier->GetCountryTag());
}