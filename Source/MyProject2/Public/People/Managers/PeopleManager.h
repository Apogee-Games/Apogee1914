#pragma once
#include "People/Description/PersonDescription.h"

#include "PeopleManager.generated.h"

UCLASS()
class UPeopleManager: public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	const TArray<FPersonDescription*>& GetPeopleByProfession(const FName& Profession);
private:
	TMap<FName, TArray<FPersonDescription*>> ProfessionPeople;
};
