#pragma once
#include "Economics/Description/GoodDescription.h"
#include "GoodBalance.generated.h"

UCLASS()
class UGoodBalance : public UObject
{
	GENERATED_BODY()
	
public:
	UGoodBalance();

	int32 GetBalance() const;
	
	int32 Supply(int32 SuppliedAmount);
	
	int32 Demand(int32 DemandedAmount);

	float GetPrice(int32 GoodAmount) const;
	
	void Init(const FGoodDescription* GoodDescription);
	
	int32 GetSupply() const;
	
	int32 GetDemand() const;

	const FGoodDescription* GetGoodDescription() const;
	
private:
	int32 DemandAmount;
	
	int32 SupplyAmount;

	const FGoodDescription* GoodDescription;
};
