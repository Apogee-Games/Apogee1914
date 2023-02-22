#include "../Public/Strata.h"

UStrata::UStrata()
{
}

void UStrata::Init()
{
	StrataMarket = NewObject<UMarket>();
}
