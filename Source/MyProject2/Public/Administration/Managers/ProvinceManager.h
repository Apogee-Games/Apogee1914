#pragma once
#include "Scenario.h"
#include "Administration/Instances/Province.h"
#include "Administration/Interfaces/Observable/ProvinceControllingCountryObservable.h"
#include "ProvinceManager.generated.h"

class UUnit;

UCLASS(Blueprintable)
class UProvinceManager : public UGameInstanceSubsystem, public IProvinceControllingCountryObservable
{
	GENERATED_BODY()
public:
	void SetScenario(UScenario* Scenario);
	
	UProvince* GetProvince(const FColor& Color) const;

	const TArray<UProvince*>& GetAllProvinces() const;
private:
	UPROPERTY()
	TMap<FColor, UProvince*> ProvinceMap;

	UPROPERTY()
	TArray<UProvince*> ProvincesArray;

	void Clear();

	void Init(UScenario* Scenario);
};
