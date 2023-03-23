#include "Administration/Instances/Parliament.h"

void UParliament::Init(FParliamentDescription* Description)
{
	for (auto& Fraction: Description->Fractions)
	{
		FractionsMap.Add(Fraction.IdeologyTag, Fraction);
	}
}

const TMap<FName, FFractionDescription>& UParliament::GetFractionsMap() const
{
	return FractionsMap;
}
