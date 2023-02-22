#pragma once
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

	void Init(const FBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince);
	
	void Init(const FBuildingInstanceDescription* BuildingInstanceDescription, const FBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince);
		
	const FBuildingDescription* GetBuildingDescription() const;

	int32 GetLabours() const;

	UProvince* GetProvince() const;

private:
	const FBuildingDescription* BuildingDescription;

	int32 Labours;

	UPROPERTY()
	UProvince* Province;
}; 