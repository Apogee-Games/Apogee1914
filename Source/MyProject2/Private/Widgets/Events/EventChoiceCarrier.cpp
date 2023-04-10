
#include "Widgets/Events/EventChoiceCarrier.h"

#include "Administration/Descriptions/Country/CountryDescription.h"

void UEventChoiceCarrier::Init(const FEventChoice& ProvidedChoice, UCountryDescription* ProvidedCountryDescription,
                               UEventDescription* ProvidedEventDescription, const TMap<FName, bool>& ProvidedChoicesConditionsEvaluated)
{
	Choice = &ProvidedChoice;
	CountryDescription = ProvidedCountryDescription;
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

UCountryDescription* UEventChoiceCarrier::GetCountryDescription() const
{
	return CountryDescription;
}
