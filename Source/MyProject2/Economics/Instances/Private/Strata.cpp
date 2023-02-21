#include "../Public/Strata.h"

UStrata::UStrata()
{
}

void UStrata::Initialize()
{
	StrataMarket = NewObject<UMarket>();
}
