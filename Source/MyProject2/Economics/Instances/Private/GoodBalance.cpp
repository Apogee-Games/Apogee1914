#include "../Public/GoodBalance.h"

UGoodBalance::UGoodBalance()
{
}

int32 UGoodBalance::GetBalance() const
{
	return SupplyAmount-DemandAmount;
}

int32 UGoodBalance::Supply(const int32 SuppliedAmount)
{
	SupplyAmount += SuppliedAmount;
	return SupplyAmount;
}
int32 UGoodBalance::Demand(const int32 DemandedAmount)
{
	DemandAmount += DemandedAmount;
	return DemandAmount;
}

float UGoodBalance::GetPrice(const int32 GoodAmount) const
{
	return GoodAmount*GoodDescription->AveragePrice;
}

void UGoodBalance::Init(const FGoodDescription* ArgGoodDescription)
{
	this->GoodDescription = ArgGoodDescription;
}

int32 UGoodBalance::GetSupply() const
{
	return SupplyAmount;
}

int32 UGoodBalance::GetDemand() const
{
	return DemandAmount;
}

const FGoodDescription* UGoodBalance::GetGoodDescription() const
{
	return GoodDescription;
}
