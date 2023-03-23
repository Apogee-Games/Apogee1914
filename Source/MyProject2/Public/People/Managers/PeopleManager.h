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

	UPerson* GetPerson(const FName& PersonId) const;
	
	const TArray<UPerson*>& GetPeopleByProfession(const FName& Profession, const FName& CountryTag);
private:
	UPROPERTY()
	TMap<FName, UPerson*> People;
	
	TMap<FName, TMap<FName, TArray<UPerson*>>> CountryProfessionPeople;

	void Clear();

	void Init(UScenario* Scenario);
};
