#include "Administration/Instances/Parliament.h"

void UParliament::Init(const FParliamentDescription& Description)
{
	Name = Description.Name;
	for (auto& FractionDescription: Description.Fractions)
	{
		UFraction* Fraction = NewObject<UFraction>(this);
		Fraction->Init(FractionDescription);
		Fractions.Add(FractionDescription.Ideology, Fraction);
	}
}

const FText& UParliament::GetName() const
{
	return Name;
}

const TMap<UIdeologyDescription*, UFraction*>& UParliament::GetFractionsMap() const
{
	return Fractions;
}
