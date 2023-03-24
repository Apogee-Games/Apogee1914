#pragma once
#include "Scenario.h"
#include "Administration/Descriptions/LawDescription.h"
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "LawManager.generated.h"

UCLASS(Abstract, Blueprintable)
class ULawManager: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);

	const TArray<FLawDescription*>& GetCommonLaws() const;

	const TArray<FLawDescription*>& GetCountrySpecificLaw(UCountry* Country);

	const TArray<FLawDescription*>& GetCountrySpecificLaw(const FName& CountryTag);
private:
	TArray<FLawDescription*> CommonLaws;

	TMap<FName, TArray<FLawDescription*>> CountrySpecificLaws;
	
	void Clear();

	void Init(UScenario* Scenario);
};