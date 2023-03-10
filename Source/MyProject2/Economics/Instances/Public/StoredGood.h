#pragma once

#include "StoredGood.generated.h"

class UStorage;
UCLASS()
class UStoredGood: public UObject
{
	GENERATED_BODY()
public:
	void Init(FName ProvidedGoodName, int32 ProvidedAmount, UStorage* ProvidedStorage);

	void Supply(int32 SuppliedAmount);

	int32 GetAmount();

	int32 Demand(int32 DemandedAmount);

	const FName& GetGoodName() const;

	UStorage* GetStorage() const;

private:
	FName GoodName;

	int32 Amount;

	UStorage* Storage;
};