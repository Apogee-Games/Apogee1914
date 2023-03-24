#include "Diplomacy/Instances/Alliance.h"
#include "Administration/Instances/Country.h"

void UAlliance::Init(UCountry* ProvidedAllianceLeader, const FText& ProvidedAllianceName, const TArray<UCountry*>& InvitedCountries)
{
	Init(ProvidedAllianceLeader, ProvidedAllianceName);

	for (const auto& InvitedCountry: InvitedCountries)
	{
		AddMember(InvitedCountry);
	}
}

void UAlliance::Init(UCountry* ProvidedAllianceLeader, const FText& ProvidedAllianceName)
{
	ProvidedAllianceLeader->SetAlliance(this);
	AllianceLeader = ProvidedAllianceLeader;
	Members.Add(AllianceLeader);
	AllianceName = ProvidedAllianceName;
}

void UAlliance::AddMember(UCountry* Country)
{
	for (const auto& Member: Members)
	{
		Member->SetRelation(Country, Allied);
		Country->SetRelation(Member, Allied);
	}
	
	Members.Add(Country);
	Country->SetAlliance(this);
}

void UAlliance::RemoveMember(UCountry* Country)
{
	Members.Remove(Country);
	Country->SetAlliance(nullptr);

	//TODO: Check for leader and do leadership migration 
	
	for (const auto& Member: Members)
	{
		Member->SetRelation(Country, Neutral);
		Country->SetRelation(Member, Neutral);
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

bool UAlliance::CountryCanJoin(UCountry* Country)
{
	for (const auto& Member: Members)
	{
		if (Country->IsCountryInWarWith(Member))
		{
			return false;
		}
	}
	return true;
}

bool UAlliance::IsCountryMember(UCountry* Country) const
{
	return Members.Contains(Country);
}

UCountry* UAlliance::GetLeader() const
{
	return AllianceLeader;
}

bool UAlliance::IsCountryLeader(UCountry* Country) const
{
	return AllianceLeader == Country;
}

void UAlliance::Dissolve()
{
	for (const auto& MemberA: Members)
	{
		for (const auto& MemberB: Members)
		{
			MemberA->SetRelation(MemberB, Neutral);
			MemberB->SetRelation(MemberA, Neutral);
		}
	}
	
	for (const auto& Member: Members)
	{
		Member->SetAlliance(nullptr);
	}

	// TODO: Add removal observer :)
}

int UAlliance::Size() const
{
	return Members.Num();
}
