#include "Administration/Instances/Fraction.h"

#include "Administration/Managers/IdeologyManager.h"

void UFraction::Init(const FFractionDescription& ProvidedFractionDescription)
{
	Ideology = GetWorld()->GetGameInstance()->GetSubsystem<UIdeologyManager>()->GetIdeology(ProvidedFractionDescription.IdeologyTag);
	FractionName = ProvidedFractionDescription.FractionName;
	MembersNumber = ProvidedFractionDescription.MembersNumber;
}

UIdeology* UFraction::GetIdeology() const
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
