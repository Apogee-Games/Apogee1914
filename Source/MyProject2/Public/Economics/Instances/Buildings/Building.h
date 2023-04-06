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
	
	UBuildingDescription* GetDescription() const;

	template<class T>
	T* GetDescription() const
	{
		return Cast<T>(BuildingDescription);
	}
	
	virtual void Tick();
	
	UProvince* GetProvince() const;

	const FText& GetName() const;
protected:
	UPROPERTY()
	UBuildingDescription* BuildingDescription;

	UPROPERTY()
	UProvince* Province;
};
