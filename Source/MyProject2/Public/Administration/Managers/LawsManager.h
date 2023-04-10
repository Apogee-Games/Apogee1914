#pragma once
#include "Scenario.h"
#include "Administration/Descriptions/Law/LawsGroup.h"
#include "Administration/Instances/Country.h"
#include "Blueprint/UserWidget.h"
#include "LawsManager.generated.h"

UCLASS(Abstract, Blueprintable)
class ULawsManager: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);

	const TArray<ULawsGroup*>& GetCommonLaws() const;

	const TArray<ULawsGroup*>& GetCountrySpecificLaw(UCountry* Country);

	const TArray<ULawsGroup*>& GetCountrySpecificLaw(UCountryDescription* CountryDescription);
private:
	UPROPERTY()
	TArray<ULawsGroup*> CommonLawsGroups;

	TMap<UCountryDescription*, TArray<ULawsGroup*>> CountrySpecificLawsGroups;
	
	void Clear();

	void Init(UScenario* Scenario);
};