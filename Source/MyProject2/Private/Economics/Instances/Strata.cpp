
#include "Economics/Instances/Strata.h"

UStrata::UStrata()
{
}

void UStrata::Init(const FName& ProvidedType)
{
	StrataMarket = NewObject<UMarket>();
	Storage = NewObject<UStorage>();
	Type = ProvidedType;
	Storage->Init(Type);
}

UStorage* UStrata::GetStorage() const
{
	return Storage;
}
