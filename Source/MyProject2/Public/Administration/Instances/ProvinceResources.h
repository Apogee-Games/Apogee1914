#pragma once
#include "ProvinceResource.h"
#include "Economics/Description/Goods/GoodDescription.h"

#include "ProvinceResources.generated.h"

UCLASS()
class UProvinceResources: public UObject
{
	GENERATED_BODY()
public:
	void Init(const TMap<UResourceDescription*, int32>& ProvidedResources);
	
	void AddResource(UResourceDescription* ResourceDescription, int32 Amount);
	
	void AddResource(UProvinceResource* ProvinceResource);

	int32 GetFreeAmount(UResourceDescription* Resource) const;

	int32 Use(UResourceDescription* Resource, int32 AmountToUse);

	void Free(UResourceDescription* Resource, int32 Amount);

	UProvinceResource* GetResource(UResourceDescription* Resource) const;

	const TMap<UResourceDescription*, UProvinceResource*>& GetMap() const;
private:
	UPROPERTY()
	TMap<UResourceDescription*, UProvinceResource*> Resources;
};
