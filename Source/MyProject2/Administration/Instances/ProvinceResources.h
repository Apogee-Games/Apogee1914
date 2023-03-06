#pragma once
#include "ProvinceResource.h"

#include "ProvinceResources.generated.h"

UCLASS()
class UProvinceResources: public UObject
{
	GENERATED_BODY()
public:
	void AddResource(uint8* ResourceDescription, int32 Amount);
	
	void AddResource(UProvinceResource* ProvinceResource);

	int32 GetFreeAmount(const FName& ResourceName) const;

	int32 Use(const FName& ResourceName, int32 AmountToUse);

	void Free(const FName& ResourceName, int32 Amount);

	UProvinceResource* GetResource(const FName& ResourceName) const;

	const TMap<FName, UProvinceResource*>& GetMap() const;
private:
	UPROPERTY()
	TMap<FName, UProvinceResource*> Resources;
};
