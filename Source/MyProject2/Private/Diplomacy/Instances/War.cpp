#include "Diplomacy/Instances/War.h"

#include "MyGameInstance.h"
#include "Diplomacy/Managers/RelationshipsManager.h"

void UWar::Init(UCountry* ProvidedAttackerLeader, UCountry* ProvidedDefenderLeader)
{
	AttackerLeader = ProvidedAttackerLeader;
	DefenderLeader = ProvidedDefenderLeader;

	Cast<URelationshipsManager>(GetOuter())->SetWarRelation(AttackerLeader, DefenderLeader);
	
	Attackers.Add(ProvidedAttackerLeader);
	Defenders.Add(DefenderLeader);
}

void UWar::AddAttacker(UCountry* Country)
{
	Attackers.Add(Country);

	URelationshipsManager* RelationshipsManager = Cast<URelationshipsManager>(GetOuter());

	for (const auto& Defender: Defenders)
	{
		RelationshipsManager->SetWarRelation(Country, Defender);
	}
}

void UWar::AddDefender(UCountry* Country)
{
	Defenders.Add(Country);
	
	URelationshipsManager* RelationshipsManager = Cast<URelationshipsManager>(GetOuter());

	for (const auto& Attacker: Attackers)
	{
		RelationshipsManager->SetWarRelation(Attacker, Country);
	}
}

UCountry* UWar::GetAttackerLeader() const
{
	return AttackerLeader;
}

UCountry* UWar::GetDefenderLeader() const
{
	return DefenderLeader;
}

const TArray<UCountry*>& UWar::GetAttackers() const
{
	return Attackers;
}

const TArray<UCountry*>& UWar::GetDefenders() const
{
	return Defenders;
}

bool UWar::CountryParticipates(UCountry* Country) const
{
	return Attackers.Contains(Country) || Defenders.Contains(Country);
}
