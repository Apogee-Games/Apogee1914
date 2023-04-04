#pragma once
#include "Economics/Description/Buildings/BuildingDescription.h"
#include "Interfaces/Ownable.h"
#include "Building.generated.h"

class UProvince;

UCLASS()
class UBuilding : public UObject, public IOwnable
{
	GENERATED_BODY()
public:
	virtual void Init(UBuildingDescription* ProvidedBuildingDescription, UProvince* ProvidedProvince);
	
	UBuildingDescription* GetBuildingDescription() const;

	virtual void Tick();
	
	UProvince* GetProvince() const;
protected:
	UPROPERTY()
	UBuildingDescription* BuildingDescription;

	UPROPERTY()
	UProvince* Province;

	template<class T>
	T* GetDescription()
	{
		return Cast<T>(BuildingDescription);
	}
};
