
#include "Administration/Instances/ProvinceResource.h"

void UProvinceResource::Init(UResourceDescription* ProvidedResourceDescription, int32 ProvidedAmount)
{
	ResourceDescription = ProvidedResourceDescription;
	Amount = ProvidedAmount;
	UsedAmount = 0;
}

int32 UProvinceResource::GetFreeAmount() const
{
	return Amount - UsedAmount;
}

int32 UProvinceResource::GetUsedAmount() const
{
	return UsedAmount;
}

int32 UProvinceResource::GetTotalAmount() const
{
	return Amount;
}

int32 UProvinceResource::Use(int32 AmountToUse)
{
	const int32 CanProvide = FMath::Min(AmountToUse, Amount - UsedAmount);
	UsedAmount += CanProvide;
	return CanProvide;
}

void UProvinceResource::Free(int32 AmountToFree)
{
	UsedAmount = FMath::Max(0, UsedAmount - AmountToFree);
}

UResourceDescription* UProvinceResource::GetResource() const
{
	return ResourceDescription;
}