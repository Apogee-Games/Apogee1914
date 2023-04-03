#pragma once
#include "Storage.h"
#include "Economics/Description/BuildingInstanceDescription.h"
#include "Economics/Description/Buildings/BuildingDescription.h"
#include "Interfaces/Ownable.h"
#include "Building.generated.h"

class UProvince;

UCLASS()
class UBuilding : public UObject, public IOwnable
{
	GENERATED_BODY()
public:
	//void Produce();

	void Init(UBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince);
	
	void Init(const FBuildingInstanceDescription* BuildingInstanceDescription, UBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince, UStorage* ProvidedStorage);
		
	UBuildingDescription* GetBuildingDescription() const;

	//int32 GetLabours() const;

	// int32 GetMaxLabours() const;

	UProvince* GetProvince() const;
	
	// const FName& GetBuildingName() const;
private:
	UPROPERTY()
	UBuildingDescription* BuildingDescription;

	int32 Labours;

	UPROPERTY()
	UProvince* Province;

	// int32 GetPossibleProductOutputCount() const;

	// void DemandGoods(int32 ProductCount);

	// void SupplyGoods(int32 ProductCount);

	// UStorage* GetStorage() const;
};