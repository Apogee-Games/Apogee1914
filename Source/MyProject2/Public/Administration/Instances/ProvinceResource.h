#pragma once
#include "Administration/Descriptions/ResourceDescription.h"

#include "ProvinceResource.generated.h"

UCLASS()
class UProvinceResource: public UObject
{
	GENERATED_BODY()
public:
	void Init(uint8* ProvidedResourceDescription, int32 ProvidedAmount);
	
	void Init(FResourceDescription* ProvidedResourceDescription, int32 ProvidedAmount);

	int32 GetFreeAmount() const;

	int32 GetUsedAmount() const;

	int32 GetTotalAmount() const;

	int32 Use(int32 AmountToUse);

	void Free(int32 AmountToFree);

	const FName& GetResourceName() const;

private:
	FResourceDescription* ResourceDescription;

	int32 Amount;

	int32 UsedAmount;
};
