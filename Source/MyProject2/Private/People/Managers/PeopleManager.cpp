#include "People/Managers/PeopleManager.h"

void UPeopleManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

UPerson* UPeopleManager::GetPerson(UPersonDescription* PersonDescription) const
{
	return People.Contains(PersonDescription) ? People[PersonDescription] : nullptr;
}

const TArray<UPerson*>& UPeopleManager::GetPeopleByProfession(UProfessionDescription* Profession, UCountryDescription* Country)
{
	if (!CountryProfessionPeople.Contains(Country))
	{
		CountryProfessionPeople.Add(Country, {});
	} else if (!CountryProfessionPeople[Country].Contains(Profession))
	{
		CountryProfessionPeople[Country].Add(Profession, {});
	}
	return CountryProfessionPeople[Country][Profession];
}

const TMap<UProfessionDescription*, TArray<UPerson*>>& UPeopleManager::GetCountryPeople(UCountryDescription* Country) const
{
	return CountryProfessionPeople[Country];
}

const TMap<UPersonDescription*, UPerson*>& UPeopleManager::GetPeople() const
{
	return People;
}

void UPeopleManager::Clear()
{
	for (const auto& [Name, Person] : People)
	{
		Person->MarkAsGarbage();
	}

	People.Empty();
	CountryProfessionPeople.Empty();
}

void UPeopleManager::Init(UScenario* Scenario)
{
	for (const auto& [Country, CountryPeopleDescriptions]: Scenario->PeopleDescriptions)
	{
		TMap<UProfessionDescription*, TArray<UPerson*>> CountryPeople;
		for (const auto& [Profession, Group]: CountryPeopleDescriptions->ProfessionGroups)
		{
			TArray<UPerson*> PeopleList;
			for (const auto& Description: Group->PeopleDescriptions)
			{
				if (People.Contains(Description)) continue;
				UPerson* Person = NewObject<UPerson>(this);
				Person->Init(Description);
				People.Add(Description, Person);
				PeopleList.Add(Person);
			}
			CountryPeople.Add(Profession, PeopleList);
		}
		CountryProfessionPeople.Add(Country, CountryPeople);
	}
}
