
#include "Administration/Instances/ProvinceResources.h"

void UProvinceResources::Init(const TMap<UResourceDescription*, int32>& ProvidedResources)
{
	for (const auto& [Resource, Amount]: ProvidedResources)
	{
		AddResource(Resource, Amount);
	}
}

void UProvinceResources::AddResource(UResourceDescription* ResourceDescription, int32 Amount)
{
	if (!ResourceDescription) return;
	UProvinceResource* Resource = NewObject<UProvinceResource>(this);
	Resource->Init(ResourceDescription, Amount);
	Resources.Add(Resource->GetResource(), Resource);
}

void UProvinceResources::AddResource(UProvinceResource* ProvinceResource)
{
	Resources.Add(ProvinceResource->GetResource(), ProvinceResource);
}

int32 UProvinceResources::GetFreeAmount(UResourceDescription* Resource) const
{
	return Resources.Contains(Resource) ? Resources[Resource]->GetFreeAmount(): 0;
}

int32 UProvinceResources::Use(UResourceDescription* Resource, int32 AmountToUse)
{
	return Resources.Contains(Resource) ? Resources[Resource]->Use(AmountToUse) : 0;
}

void UProvinceResources::Free(UResourceDescription* Resource, int32 Amount)
{
	if (!Resources.Contains(Resource)) return;
	Resources[Resource]->Free(Amount);
}

UProvinceResource* UProvinceResources::GetResource(UResourceDescription* Resource) const
{
	return Resources.Contains(Resource) ? Resources[Resource]: nullptr;
}

const TMap<UResourceDescription*, UProvinceResource*>& UProvinceResources::GetMap() const
{
	return Resources;
}
