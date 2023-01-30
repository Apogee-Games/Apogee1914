#pragma once
#include "Province.h"
#include "MyProject2/Administration/Descriptions/StateDescription.h"
#include "MyProject2/Administration/Managers/ProvinceManager.h"

#include "State.generated.h"

UCLASS()
class UState : public UObject 
{
	GENERATED_BODY()
public:

	void Init(FStateDescription* StateDescription, const UProvinceManager* ProvinceManager);

	const FString& GetName() const;

	TArray<UProvince*> GetProvinces() const;
	
private:
	FString Name;

	UPROPERTY()
	TArray<UProvince*> Provinces;
};
