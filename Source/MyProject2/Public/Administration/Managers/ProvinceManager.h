#pragma once
#include "Scenario.h"
#include "Administration/Instances/Province.h"
#include "Interfaces/BaseManager.h"
#include "ProvinceManager.generated.h"

class UUnit;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnProvinceHasNewOwner, UProvince*, UCountry*, UCountry*) 
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnProvinceHasNewController, UProvince*, UCountry*, UCountry*)

UCLASS(Abstract, Blueprintable)
class UProvinceManager : public UBaseManager
{
	GENERATED_BODY()
public:
	virtual void SetScenario(UScenario* Scenario) override;
	
	UProvince* GetProvince(const FColor& Color) const;

	const TArray<UProvince*>& GetAllProvinces() const;

	virtual ELoadStage GetLoadStage() override;

	FOnProvinceHasNewOwner OnProvinceHasNewOwner;
	FOnProvinceHasNewController OnProvinceHasNewController;
private:
	UPROPERTY()
	TMap<FColor, UProvince*> ProvinceMap;

	UPROPERTY()
	TArray<UProvince*> ProvincesArray;

	void Clear();

	void Init(UScenario* Scenario);
};
