#include "People/Managers/PeopleManager.h"

void UPeopleManager::SetScenario(UScenario* Scenario)
{
	UDataTable* PeoplesDescriptions = Scenario->PeoplesDescriptions;
	
	for (const auto & [Id, Description]: PeoplesDescriptions->GetRowMap())
	{
		FPersonDescription* CastedDescription = reinterpret_cast<FPersonDescription*>(Description);

		UPerson* Person = NewObject<UPerson>(this);
		Person->Init(Id, CastedDescription);
		
		People.Add(Person->GetId(), Person);

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

UPerson* UPeopleManager::GetPerson(const FName& PersonId) const
{
	return People.Contains(PersonId) ? People[PersonId] : nullptr;
}

const TArray<UPerson*>& UPeopleManager::GetPeopleByProfession(const FName& Profession, const FName& CountryTag)
{
	if (!CountryProfessionPeople.Contains(CountryTag))
	{
		CountryProfessionPeople.Add(CountryTag, {
			{CountryTag, {}}
		});
	}
	if (!CountryProfessionPeople[CountryTag].Contains(Profession))
	{
		CountryProfessionPeople[CountryTag].Add(Profession, {});
	}
 	return CountryProfessionPeople[CountryTag][Profession];
}
