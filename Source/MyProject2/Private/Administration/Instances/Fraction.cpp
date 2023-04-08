#include "Administration/Instances/Fraction.h"

void UFraction::Init(const FFractionDescription& ProvidedFractionDescription)
{
	Ideology = ProvidedFractionDescription.Ideology;
	FractionName = ProvidedFractionDescription.Name;
	MembersNumber = ProvidedFractionDescription.MembersNumber;
}

UIdeologyDescription* UFraction::GetIdeology() const
{
	return Ideology;
}

const FText& UFraction::GetFractionName() const
{
	return FractionName;
}

int32 UFraction::GetMembersNumber() const
{
	return MembersNumber;
}
