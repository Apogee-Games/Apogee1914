#pragma once
#include "Events/Description/EventDescription.h"

#include "EventChoiceCarrier.generated.h"

UCLASS()
class UEventChoiceCarrier : public UObject
{
	GENERATED_BODY()
public:
	void Init(const FEventChoice& ProvidedChoice, const FName& ProvidedCountryTag,
	          UEventDescription* ProvidedEventDescription,
	          const TMap<FName, bool>& ProvidedChoicesConditionsEvaluated);

	const FText& GetChoiceText() const;

	bool IsChoiceActive() const;

	UEventDescription* GetEventDescription() const;

	const FName& GetChoiceName() const;

	const FName& GetCountryTag() const;
	
private:
	const FEventChoice* Choice;
	
	const FName* CountryTag;

	UPROPERTY()
	UEventDescription* EventDescription;
	
	TMap<FName, bool> ChoicesConditionsEvaluated;
};
