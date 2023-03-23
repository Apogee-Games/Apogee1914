#include "Administration/Instances/Parliament.h"

void UParliament::Init(FParliamentDescription* Description)
{
	ParliamentName = Description->ParliamentName;
	for (auto& FractionDescription: Description->Fractions)
	{
		UFraction* Fraction = NewObject<UFraction>(this);
		Fraction->Init(FractionDescription);
		Fractions.Add(FractionDescription.IdeologyTag, Fraction);
	}
}

const FText& UParliament::GetName() const
{
	return ParliamentName;
}

const TMap<FName, UFraction*>& UParliament::GetFractionsMap() const
{
	return Fractions;
}
