#include "Diplomacy/Instances/War.h"
#include "Administration/Instances/Country.h"

void UWar::Init(UCountry* ProvidedAttackerLeader, UCountry* ProvidedDefenderLeader)
{
	AttackerLeader = ProvidedAttackerLeader;
	DefenderLeader = ProvidedDefenderLeader;
	
	AttackerLeader->SetRelation(DefenderLeader, ERelationType::War);
	DefenderLeader->SetRelation(AttackerLeader, ERelationType::War);

	AttackerLeader->AddWar(this);
	DefenderLeader->AddWar(this);

	Attackers.Add(ProvidedAttackerLeader);
	Defenders.Add(DefenderLeader);
	
	for (const auto& [Country, Relation]: DefenderLeader->GetRelations())
	{
		if (Country->MustHelpInDefenciveWar(DefenderLeader))
		{
			AddDefender(Country);
		}
	}

	for (const auto& [Country, Relation]: AttackerLeader->GetRelations())
	{
		if (Country->MustHelpInAggressiveWar(AttackerLeader))
		{
			AddAttacker(Country);
		}
	}

	URelationshipsManager* RelationshipsManager = Cast<URelationshipsManager>(GetOuter());
	RelationshipsManager->OnWarStatusChanged.Broadcast(this, EWarStatus::Declared);
}

void UWar::AddAttacker(UCountry* Country)
{
	Country->AddWar(this);
	Attackers.Add(Country);

	for (const auto& Defender: Defenders)
	{
		Country->SetRelation(Defender, ERelationType::War);
		Defender->SetRelation(Country, ERelationType::War);
	}
}

void UWar::AddDefender(UCountry* Country)
{
	Country->AddWar(this);
	Defenders.Add(Country);
	
	for (const auto& Attacker: Attackers)
	{
		Country->SetRelation(Attacker, ERelationType::War);
		Attacker->SetRelation(Country, ERelationType::War);
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

bool UWar::IsMember(UCountry* Country) const
{
	return Attackers.Contains(Country) || Defenders.Contains(Country);
}

void UWar::AddCountryOnSide(UCountry* Country, UCountry* OnSideOfCountry)
{
	if (Attackers.Contains(OnSideOfCountry))
	{
		AddAttacker(Country);
	} else
	{
		AddDefender(Country);
	}
}

void UWar::End()
{
	for (UCountry* Defender: Defenders)
	{
		for (UCountry* Attacker: Attackers)
		{
			Defender->SetRelation(Attacker, ERelationType::Neutral);
			Attacker->SetRelation(Defender, ERelationType::Neutral);
		}
	}
	
	URelationshipsManager* RelationshipsManager = Cast<URelationshipsManager>(GetOuter());
	RelationshipsManager->OnWarStatusChanged.Broadcast(this, EWarStatus::Ended);
}
