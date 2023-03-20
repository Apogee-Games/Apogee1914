
#include "Diplomacy/Managers/RelationshipsManager.h"

#include "Administration/Managers/CountriesManager.h"
#include "Diplomacy/Instances/War.h"

void URelationshipsManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

bool URelationshipsManager::CanDeclareWar(UCountry* CountryA, UCountry* CountryB)
{
	return (CanDeclareWarList & Relations[CountryA][CountryB]) != 0;
}

bool URelationshipsManager::CanCreateNonAggressionPact(UCountry* CountryA, UCountry* CountryB)
{
	return (CanCreateNonAggressionPactList & Relations[CountryA][CountryB]) != 0;
}

bool URelationshipsManager::CanCreateDefencivePact(UCountry* CountryA, UCountry* CountryB)
{
	return (CanCreateDefencivePactList & Relations[CountryA][CountryB]) != 0;
}

bool URelationshipsManager::CanCreateAlliance(UCountry* CountryA, UCountry* CountryB)
{
	return (CanCreateAllianceList & Relations[CountryA][CountryB]) != 0;
}

void URelationshipsManager::SetWarRelation(UCountry* CountryA, UCountry* CountryB)
{
	Relations[CountryA][CountryB] = War;
	Relations[CountryB][CountryA] = War;
}

void URelationshipsManager::DeclareWar(UCountry* CountryA, UCountry* CountryB)
{
	UWar* WarInstance = NewObject<UWar>(this);

	WarInstance->Init(CountryA, CountryB);
	
	for (const auto& [Country, Relation]: Relations[CountryB])
	{
		if (Relation == DefencivePact)
		{
			WarInstance->AddDefender(Country);
		}
	}

	NotifyWarDeclaration(WarInstance);
}

void URelationshipsManager::CreateNonAggressionPact(UCountry* CountryA, UCountry* CountryB)
{
	Relations[CountryA][CountryB] = NonAggressionPact;
	Relations[CountryB][CountryA] = NonAggressionPact;
}

void URelationshipsManager::CreateDefencivePact(UCountry* CountryA, UCountry* CountryB)
{
	Relations[CountryA][CountryB] = DefencivePact;
	Relations[CountryB][CountryA] = DefencivePact;
}

ERelationType URelationshipsManager::GetRelation(UCountry* CountryA, UCountry* CountryB)
{
	return Relations[CountryA][CountryB];
}

const TMap<UCountry*, ERelationType>& URelationshipsManager::GetRelations(UCountry* Country)
{
	return Relations[Country];
}

void URelationshipsManager::Clear()
{
	Relations.Empty();
}

void URelationshipsManager::Init(UScenario* Scenario)
{
	TArray<UCountry*> Countries;
	GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountryMap().GenerateValueArray(Countries);

	for (const auto& CountryA: Countries)
	{
		Relations.Add(CountryA, {});
		for (const auto& CountryB: Countries)
		{
			Relations[CountryA].Add(CountryB, Neutral);
		}
	}

	UCountry* France = GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry("FRA");
	UCountry* Spain = GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry("SPA");
	DeclareWar(France, Spain);
}
