#include "People/Managers/PeopleManager.h"

void UPeopleManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UDataTable* PeoplesDescriptions = LoadObject<UDataTable>(nullptr, TEXT("/Game/Sources/people_desctiption"));
	
	if(!PeoplesDescriptions) return;
	
	for (const auto & [Name, Description]: PeoplesDescriptions->GetRowMap())
	{
		FPersonDescription* CastedDescription = reinterpret_cast<FPersonDescription*>(Description);

		UPerson* Person = NewObject<UPerson>(GetWorld());
		Person->Init(CastedDescription);
		
		People.Add(Person);

		if (!CountryProfessionPeople.Contains(CastedDescription->CountryTag))
		{
			CountryProfessionPeople.Add(CastedDescription->CountryTag, {});
		}
		
		for (const auto& ProfessionName: CastedDescription->Professions)
		{
			if (!CountryProfessionPeople[CastedDescription->CountryTag].Contains(ProfessionName))
			{
				CountryProfessionPeople[CastedDescription->CountryTag].Add(ProfessionName, {});
			}
			CountryProfessionPeople[CastedDescription->CountryTag][ProfessionName].Add(Person);
		}
	}
}

const TArray<UPerson*>& UPeopleManager::GetPeopleByProfession(const FName& Profession, const FName& CountryTag)
{
	return CountryProfessionPeople[CountryTag][Profession];
}
