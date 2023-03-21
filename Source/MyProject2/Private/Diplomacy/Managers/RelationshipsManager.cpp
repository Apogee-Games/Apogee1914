
#include "Diplomacy/Managers/RelationshipsManager.h"

#include "Administration/Managers/CountriesManager.h"
#include "Diplomacy/Instances/Alliance.h"
#include "Diplomacy/Instances/War.h"
#include "Maps/Diplomacy/AlliancesMap.h"
#include "Maps/Diplomacy/CountryRelationMap.h"

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

void URelationshipsManager::SetRelation(UCountry* CountryA, UCountry* CountryB, ERelationType Relation)
{
	Relations[CountryA][CountryB] = Relation;
	Relations[CountryB][CountryA] = Relation;
}

void URelationshipsManager::DeclareWar(UCountry* CountryA, UCountry* CountryB)
{
	UWar* WarInstance = NewObject<UWar>(this);

	WarInstance->Init(CountryA, CountryB);
	
	for (const auto& [Country, Relation]: Relations[CountryB])
	{
		if (MustComeToDefense & Relation)
		{
			WarInstance->AddDefender(Country);
		}
	}

	for (const auto& [Country, Relation]: Relations[CountryA])
	{
		if (MustHelpInAggressiveWar & Relation)
		{
			WarInstance->AddAttacker(Country);
		}
	}

	for (const auto& Member: WarInstance->GetAttackers())
	{
		if (!CountriesWars.Contains(Member))
		{
			CountriesWars.Add(Member, {});
		} 
		CountriesWars[Member].Add(WarInstance);
	}

	for (const auto& Member: WarInstance->GetDefenders())
	{
		if (!CountriesWars.Contains(Member))
		{
			CountriesWars.Add(Member, {});
		} 
		CountriesWars[Member].Add(WarInstance);
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

void URelationshipsManager::CreateAlliance(UCountry* Country, const FText& AllianceName)
{
	UAlliance* Alliance = NewObject<UAlliance>(this);

	Alliance->Init(Country, AllianceName);

	NotifyAllianceCreation(Alliance);
}

void URelationshipsManager::CreateAlliance(UCountry* Country, const FText& AllianceName, const TArray<UCountry*>& InvitedCountries)
{
	UAlliance* Alliance = NewObject<UAlliance>(this);

	Alliance->Init(Country, AllianceName);

	for (const auto& InvitedCountry: InvitedCountries)
	{
		Alliance->AddMember(InvitedCountry);
	}

	NotifyAllianceCreation(Alliance);
}

ERelationType URelationshipsManager::GetRelation(UCountry* CountryA, UCountry* CountryB)
{
	return Relations[CountryA][CountryB];
}

const TMap<UCountry*, ERelationType>& URelationshipsManager::GetRelations(UCountry* Country)
{
	return Relations[Country];
}

const TArray<UWar*>& URelationshipsManager::GetCountryWars(UCountry* Country)
{
	if (!CountriesWars.Contains(Country))
	{
		CountriesWars.Add(Country, {});
	}
	return CountriesWars[Country];
}

bool URelationshipsManager::IsCountryInWar(UCountry* Country)
{
	return CountriesWars.Contains(Country) && CountriesWars[Country].Num();
}

bool URelationshipsManager::CanCountryJoinWar(UCountry* CountryA, UCountry* CountryB)
{
	return (CanJoinWar & Relations[CountryA][CountryB]) != 0; 
}

bool URelationshipsManager::IsTherePossibleWarToJoin(UCountry* CountryToJoin, UCountry* CountryToJoinTo)
{
	for (const auto& War: GetCountryWars(CountryToJoinTo))
	{
		if (!War->CountryParticipates(CountryToJoin))
		{
			return true;
		}
	}
	return false;
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
	CreateAlliance(France, FText::FromString(TEXT("West powers")), {Spain});

	GetGameInstance()->GetSubsystem<UCountryRelationMap>()->UpdateMap();
	GetGameInstance()->GetSubsystem<UAlliancesMap>()->UpdateMap();
}
