#pragma once
#include "MyProject2/Economics/Description/GoodDescription.h"
#include "GoodBalance.generated.h"

UCLASS()
class UGoodBalance : public UObject
{
	GENERATED_BODY()
public:
	UGoodBalance();

	int GetBalance() const;
	int Supply(int SuppliedAmount);
	int Demand(int DemandedAmount);

	float GetPrice(int GoodAmount) const;
	void Init(const FGoodDescription* GoodDescription);
	int GetSupply() const;
	int GetDemand() const;

	const FGoodDescription* GetGoodDescription() const;

	
private:

	int DemandAmount;
	int SupplyAmount;
	const FGoodDescription* GoodDescription;
	
};
