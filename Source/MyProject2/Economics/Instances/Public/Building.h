﻿#pragma once
#include "Storage.h"
#include "MyProject2/Economics/Description/BuildingDescription.h"
#include "MyProject2/Economics/Description/BuildingInstanceDescription.h"
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

	UProvince* GetProvince() const;

private:
	const FBuildingDescription* BuildingDescription;

	int32 Labours;

	UPROPERTY()
	UProvince* Province;

	UPROPERTY()
	UStorage* Storage;

	int GetPossibleProductOutputCount() const;

	void DemandGoods(int ProductCount);

	void SupplyGoods(int ProductCount);
};