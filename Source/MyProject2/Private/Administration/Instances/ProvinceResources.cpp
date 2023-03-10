
#include "Administration/Instances/ProvinceResources.h"

void UProvinceResources::AddResource(uint8* ResourceDescription, int32 Amount)
{
	if (!ResourceDescription) return;
	UProvinceResource* Resource = NewObject<UProvinceResource>();
	Resource->Init(ResourceDescription, Amount);
	Resources.Add(Resource->GetResourceName(), Resource);
}

void UProvinceResources::AddResource(UProvinceResource* ProvinceResource)
{
	Resources.Add(ProvinceResource->GetResourceName(), ProvinceResource);
}

int32 UProvinceResources::GetFreeAmount(const FName& ResourceName) const
{
	return Resources[ResourceName]->GetFreeAmount();
}

int32 UProvinceResources::Use(const FName& ResourceName, int32 AmountToUse)
{
	return Resources[ResourceName]->Use(AmountToUse);
}

void UProvinceResources::Free(const FName& ResourceName, int32 Amount)
{
	Resources[ResourceName]->Free(Amount);
}

UProvinceResource* UProvinceResources::GetResource(const FName& ResourceName) const
{
	return Resources[ResourceName];
}

const TMap<FName, UProvinceResource*>& UProvinceResources::GetMap() const
{
	return Resources;
}
