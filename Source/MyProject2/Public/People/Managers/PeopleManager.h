#pragma once
#include "People/Instances/Person.h"

#include "PeopleManager.generated.h"

UCLASS()
class UPeopleManager: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	const TArray<UPerson*>& GetPeopleByProfession(const FName& Profession, const FName& CountryTag);
private:
	UPROPERTY()
	TArray<UPerson*> People;
	
	TMap<FName, TMap<FName, TArray<UPerson*>>> CountryProfessionPeople;
};
