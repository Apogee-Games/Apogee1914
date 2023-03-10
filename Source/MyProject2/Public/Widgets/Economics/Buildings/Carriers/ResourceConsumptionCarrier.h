#pragma once
#include "Economics/Description/BuildingDescription.h"
#include "ResourceConsumptionCarrier.generated.h"

UCLASS()
class UResourceConsumptionCarrier : public UObject
{
	GENERATED_BODY()
public:
	void Init(const FBuildingDescription* ProvidedBuildingDescription, const FName& ProvidedResourceName);

	const FName& GetResourceName() const;

	int32 GetResourceConsumption() const;

private:
	const FBuildingDescription* BuildingDescription;

	FName ResourceName;
};
