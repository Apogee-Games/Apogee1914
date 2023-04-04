#pragma once
#include "Economics/Description/Goods/GoodDescription.h"
#include "StoredGood.generated.h"

class UStorage;
UCLASS()
class UStoredGood: public UObject
{
	GENERATED_BODY()
public:
	void Init(UGoodDescription* ProvidedGood, int32 ProvidedAmount, UStorage* ProvidedStorage);

	void Supply(int32 SuppliedAmount);

	int32 GetAmount();

	int32 Demand(int32 DemandedAmount);

	const FText& GetGoodName() const;

	UStorage* GetStorage() const;
private:
	UPROPERTY()
	UStorage* Storage;

	UPROPERTY()
	UGoodDescription* Good;

	int32 Amount;
};