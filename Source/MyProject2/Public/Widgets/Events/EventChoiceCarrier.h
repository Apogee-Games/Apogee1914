#pragma once
#include "Administration/Descriptions/Country/CountryDescription.h"
#include "Events/Description/EventDescription.h"

#include "EventChoiceCarrier.generated.h"

UCLASS()
class UEventChoiceCarrier : public UObject
{
	GENERATED_BODY()
public:
	void Init(const FEventChoice& ProvidedChoice, UCountryDescription* ProvidedCountryDescription,
	          UEventDescription* ProvidedEventDescription,
	          const TMap<FName, bool>& ProvidedChoicesConditionsEvaluated);

	const FText& GetChoiceText() const;

	bool IsChoiceActive() const;

	UEventDescription* GetEventDescription() const;

	const FName& GetChoiceName() const;

	UCountryDescription* GetCountryDescription() const;
	
private:
	const FEventChoice* Choice;

	UPROPERTY()
	UCountryDescription* CountryDescription;

	UPROPERTY()
	UEventDescription* EventDescription;
	
	TMap<FName, bool> ChoicesConditionsEvaluated;
};
