
#include "Diplomacy/Managers/RelationshipsManager.h"

#include "Administration/Managers/CountriesManager.h"
#include "Diplomacy/Instances/Alliance.h"
#include "Diplomacy/Instances/War.h"

void URelationshipsManager::SetScenario(UScenario* Scenario)
{
	Clear();
	Init(Scenario);
}

void URelationshipsManager::DeclareWar(UCountry* CountryA, UCountry* CountryB)
{
	UWar* WarInstance = NewObject<UWar>(this);

	WarInstance->Init(CountryA, CountryB);
}

void URelationshipsManager::CreateAlliance(UCountry* Country, const FText& AllianceName, const TArray<UCountry*>& InvitedCountries)
{
	UAlliance* Alliance = NewObject<UAlliance>(this);

	Alliance->Init(Country, AllianceName, InvitedCountries);
}

ELoadStage URelationshipsManager::GetLoadStage()
{
	return ELoadStage::RelationshipsManager;
}

void URelationshipsManager::Clear()
{
	
}

void URelationshipsManager::Init(UScenario* Scenario)
{
//	UCountry* France = GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry("FRA");
//	UCountry* Spain = GetGameInstance()->GetSubsystem<UCountriesManager>()->GetCountry("SPA");
//	DeclareWar(France, Spain);

}
