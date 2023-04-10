#pragma once
#include "Economics/Description/ResourceDescription.h"

#include "ProvinceResource.generated.h"

UCLASS()
class UProvinceResource: public UObject
{
	GENERATED_BODY()
public:
	void Init(UResourceDescription* ProvidedResourceDescription, int32 ProvidedAmount);

	int32 GetFreeAmount() const;

	int32 GetUsedAmount() const;

	int32 GetTotalAmount() const;

	int32 Use(int32 AmountToUse);

	void Free(int32 AmountToFree);

	UResourceDescription* GetResource() const;
private:
	UPROPERTY()
	UResourceDescription* ResourceDescription;

	int32 Amount;

	int32 UsedAmount;
};
