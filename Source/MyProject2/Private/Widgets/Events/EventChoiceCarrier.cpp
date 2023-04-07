
#include "Widgets/Events/EventChoiceCarrier.h"

void UEventChoiceCarrier::Init(const FEventChoice& ProvidedChoice, const FName& ProvidedCountryTag,
                               UEventDescription* ProvidedEventDescription, const TMap<FName, bool>& ProvidedChoicesConditionsEvaluated)
{
	Choice = &ProvidedChoice;
	CountryTag = &ProvidedCountryTag;
	EventDescription = ProvidedEventDescription;
	ChoicesConditionsEvaluated = ProvidedChoicesConditionsEvaluated;
}

const FText& UEventChoiceCarrier::GetChoiceText() const
{
	return Choice->Text;
}

bool UEventChoiceCarrier::IsChoiceActive() const
{
	return ChoicesConditionsEvaluated[Choice->Name];
}

UEventDescription* UEventChoiceCarrier::GetEventDescription() const
{
	return EventDescription;
}

const FName& UEventChoiceCarrier::GetChoiceName() const
{
	return Choice->Name;
}

const FName& UEventChoiceCarrier::GetCountryTag() const
{
	return *CountryTag;
}


