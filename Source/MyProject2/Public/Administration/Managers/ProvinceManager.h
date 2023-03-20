#pragma once
#include "Scenario.h"
#include "Administration/Instances/Province.h"
#include "Administration/Interfaces/Observable/ProvinceControllingCountryObservable.h"
#include "ProvinceManager.generated.h"

class UUnit;

UCLASS(Abstract, Blueprintable)
class UProvinceManager : public UGameInstanceSubsystem, public IProvinceControllingCountryObservable
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	UProvince* GetProvince(const FColor& ProvinceColor) const;
	
	UProvince* GetProvince(const FName& ProvinceColorHex) const;

	const TArray<UProvince*>& GetAllProvinces() const;
private:
	UPROPERTY()
	TMap<FName, UProvince*> ProvinceMap;

	UPROPERTY()
	TArray<UProvince*> ProvincesArray;

	void Clear();

	void Init(UScenario* Scenario);
};
