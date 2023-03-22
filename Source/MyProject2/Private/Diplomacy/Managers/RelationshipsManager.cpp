
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

void URelationshipsManager::DeclareWar(UCountry* CountryA, UCountry* CountryB)
{
	UWar* WarInstance = NewObject<UWar>(this);

	WarInstance->Init(CountryA, CountryB);
	
	NotifyWarDeclaration(WarInstance);
}

void URelationshipsManager::CreateNonAggressionPact(UCountry* CountryA, UCountry* CountryB)
{
	CountryA->SetRelation(CountryB, NonAggressionPact);
	CountryB->SetRelation(CountryA, NonAggressionPact);
}

void URelationshipsManager::CreateDefencivePact(UCountry* CountryA, UCountry* CountryB)
{
	CountryA->SetRelation(CountryB, DefencivePact);
	CountryB->SetRelation(CountryA, DefencivePact);
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

	Alliance->Init(Country, AllianceName, InvitedCountries);

	NotifyAllianceCreation(Alliance);
}

void URelationshipsManager::Clear()
{
	
}

void URelationshipsManager::Init(UScenario* Scenario)
{
	UCountry* France = GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry("FRA");
	UCountry* Spain = GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry("SPA");
	CreateAlliance(France, FText::FromString(TEXT("West powers")), {Spain});

	GetGameInstance()->GetSubsystem<UCountryRelationMap>()->UpdateMap();
	GetGameInstance()->GetSubsystem<UAlliancesMap>()->UpdateMap();
}
