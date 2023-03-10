#pragma once
#include "Storage.h"
#include "Economics/Description/BuildingDescription.h"
#include "Economics/Description/BuildingInstanceDescription.h"
#include "Building.generated.h"

class UProvince;

UCLASS()
class UBuilding : public UObject
{
	GENERATED_BODY()
public:
	void Produce();

	void Init(const FBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince, UStorage* ProvidedStorage);
	
	void Init(const FBuildingInstanceDescription* BuildingInstanceDescription, const FBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince, UStorage* ProvidedStorage);
		
	const FBuildingDescription* GetBuildingDescription() const;

	int32 GetLabours() const;

	int32 GetMaxLabours() const;

	UProvince* GetProvince() const;
	
	const FName& GetBuildingName() const;

private:
	const FBuildingDescription* BuildingDescription;

	int32 Labours;

	UPROPERTY()
	UProvince* Province;

	UPROPERTY()
	UStorage* Storage;

	int32 GetPossibleProductOutputCount() const;

	void DemandGoods(int32 ProductCount);

	void SupplyGoods(int32 ProductCount);
};