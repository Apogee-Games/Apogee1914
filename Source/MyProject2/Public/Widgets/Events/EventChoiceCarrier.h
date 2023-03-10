#pragma once
#include "Events/EventDescription/EventDescription.h"

#include "EventChoiceCarrier.generated.h"

UCLASS()
class UEventChoiceCarrier : public UObject
{
	GENERATED_BODY()
public:
	void Init(const FEventChoice& ProvidedChoice, const FName& ProvidedCountryTag,
	          FEventDescription* ProvidedEventDescription,
	          const TMap<FName, bool>& ProvidedChoicesConditionsEvaluated);

	const FText& GetChoiceText() const;

	bool IsChoiceActive() const;

	FEventDescription* GetEventDescription() const;

	const FName& GetChoiceName() const;

	const FName& GetCountryTag() const;
	
private:
	const FEventChoice* Choice;
	
	const FName* CountryTag;
	
	FEventDescription* EventDescription;
	
	TMap<FName, bool> ChoicesConditionsEvaluated;
};
