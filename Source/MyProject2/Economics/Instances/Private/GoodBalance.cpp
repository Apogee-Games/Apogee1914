#include "../Public/GoodBalance.h"

UGoodBalance::UGoodBalance()
{
}

int UGoodBalance::GetBalance() const
{
	return SupplyAmount-DemandAmount;
}

int UGoodBalance::Supply(const int SuppliedAmount)
{
	SupplyAmount += SuppliedAmount;
	return SupplyAmount;
}
int UGoodBalance::Demand(const int DemandedAmount)
{
	DemandAmount += DemandedAmount;
	return DemandAmount;
}

float UGoodBalance::GetPrice(const int GoodAmount) const
{
	return GoodAmount*GoodDescription->AveragePrice;
}

void UGoodBalance::Init(const FGoodDescription* ArgGoodDescription)
{
	this->GoodDescription = ArgGoodDescription;
}

int UGoodBalance::GetSupply() const
{
	return SupplyAmount;
}

int UGoodBalance::GetDemand() const
{
	return DemandAmount;
}

const FGoodDescription* UGoodBalance::GetGoodDescription() const
{
	return GoodDescription;
}
