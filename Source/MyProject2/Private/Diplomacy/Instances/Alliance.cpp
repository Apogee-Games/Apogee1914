#include "Diplomacy/Instances/Alliance.h"

#include "Diplomacy/Managers/RelationshipsManager.h"

void UAlliance::Init(UCountry* ProvidedAllianceLeader, const FText& ProvidedAllianceName)
{
	ProvidedAllianceLeader->SetAlliance(this);
	AllianceLeader = ProvidedAllianceLeader;
	Members.Add(AllianceLeader);
	AllianceName = ProvidedAllianceName;
}

void UAlliance::AddMember(UCountry* Country)
{
	URelationshipsManager* RelationshipsManager = Cast<URelationshipsManager>(GetOuter());
	for (const auto& Member: Members)
	{
		RelationshipsManager->SetRelation(Country, Member, Allied);
	}
	
	Members.Add(Country);
	Country->SetAlliance(this);

}

void UAlliance::RemoveMember(UCountry* Country)
{
	Members.Remove(Country);
	Country->SetAlliance(nullptr);

	URelationshipsManager* RelationshipsManager = Cast<URelationshipsManager>(GetOuter());
	for (const auto& Member: Members)
	{
		RelationshipsManager->SetRelation(Country, Member, Neutral);
	}
}

const FText& UAlliance::GetName() const
{
	return AllianceName;
}

FColor UAlliance::GetColor() const
{
	return AllianceLeader->GetColor();
}

bool UAlliance::IsCountryMember(UCountry* Country) const
{
	return Members.Contains(Country);
}
