#pragma once
#include "Scenario.h"
#include "People/Instances/Person.h"

#include "PeopleManager.generated.h"

UCLASS()
class UPeopleManager: public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);

	UPerson* GetPerson(UPersonDescription* PersonDescription) const;
	
	const TArray<UPerson*>& GetPeopleByProfession(UProfessionDescription* Profession, UCountryDescription* Country);

	const TMap<UProfessionDescription*, TArray<UPerson*>>& GetCountryPeople(UCountryDescription* Country) const;

	const TMap<UPersonDescription*, UPerson*>& GetPeople() const;
private:
	UPROPERTY()
	TMap<UPersonDescription*, UPerson*> People;

	TMap<UCountryDescription*, TMap<UProfessionDescription*, TArray<UPerson*>>> CountryProfessionPeople;

	void Clear();

	void Init(UScenario* Scenario);
};
