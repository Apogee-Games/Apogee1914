#pragma once
#include "Scenario.h"
#include "Interfaces/BaseManager.h"
#include "People/Instances/Person.h"

#include "PeopleManager.generated.h"

UCLASS()
class UPeopleManager: public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;

	UPerson* GetPerson(UPersonDescription* PersonDescription) const;
	
	const TArray<UPerson*>& GetPeopleByProfession(UProfessionDescription* Profession, UCountryDescription* Country);

	virtual ELoadStage GetLoadStage() override;
private:
	UPROPERTY()
	TMap<UPersonDescription*, UPerson*> People;

	TMap<UCountryDescription*, TMap<UProfessionDescription*, TArray<UPerson*>>> CountryProfessionPeople;

	void Clear();

	void Init(UScenario* Scenario);
};
