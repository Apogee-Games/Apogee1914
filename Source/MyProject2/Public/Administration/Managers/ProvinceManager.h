#pragma once
#include "Scenario.h"
#include "Administration/Instances/Province.h"
#include "Administration/Interfaces/Observable/ProvinceControllingCountryObservable.h"
#include "Interfaces/BaseManager.h"
#include "ProvinceManager.generated.h"

class UUnit;

UCLASS(Abstract, Blueprintable)
class UProvinceManager : public UBaseManager, public IProvinceControllingCountryObservable
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	UProvince* GetProvince(const FColor& Color) const;

	const TArray<UProvince*>& GetAllProvinces() const;

	virtual ELoadStage GetLoadStage() override;
private:
	UPROPERTY()
	TMap<FColor, UProvince*> ProvinceMap;

	UPROPERTY()
	TArray<UProvince*> ProvincesArray;

	void Clear();

	void Init(UScenario* Scenario);
};
