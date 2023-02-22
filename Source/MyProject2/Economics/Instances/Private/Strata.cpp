#include "../Public/Strata.h"

UStrata::UStrata()
{
}

void UStrata::Init()
{
	StrataMarket = NewObject<UMarket>();
	Storage = NewObject<UStorage>();
}

UStorage* UStrata::GetStorage() const
{
	return Storage;
}
