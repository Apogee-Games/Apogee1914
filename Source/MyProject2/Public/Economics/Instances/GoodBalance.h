#pragma once
#include "Economics/Description/Goods/GoodDescription.h"
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
	
	void Init(UGoodDescription* GoodDescription);
	
	int32 GetSupply() const;
	
	int32 GetDemand() const;

	UGoodDescription* GetGoodDescription() const;
	
private:
	int32 DemandAmount;
	
	int32 SupplyAmount;

	UPROPERTY()
	UGoodDescription* GoodDescription;
};
