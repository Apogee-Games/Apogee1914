#pragma once
#include "Province.h"
#include "Administration/Descriptions/StateDescription.h"
#include "Administration/Managers/ProvinceManager.h"

#include "State.generated.h"

UCLASS()
class UState : public UObject 
{
	GENERATED_BODY()
public:

	void Init(FStateDescription* StateDescription, const UProvinceManager* ProvinceManager);

	const FName& GetName() const;

	TArray<UProvince*> GetProvinces() const;
	
private:
	FName Name;

	UPROPERTY()
	TArray<UProvince*> Provinces;
};
