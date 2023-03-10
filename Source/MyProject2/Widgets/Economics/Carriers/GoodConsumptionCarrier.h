#pragma once
#include "MyProject2/Economics/Description/BuildingDescription.h"
#include "GoodConsumptionCarrier.generated.h"

UCLASS()
class UGoodConsumptionCarrier : public UObject
{
	GENERATED_BODY()
public:
	void Init(const FBuildingDescription* ProvidedBuildingDescription, const FName& ProvidedGoodName);

	const FName& GetGoodName() const;

	int32 GetGoodConsumption() const;

private:
	const FBuildingDescription* BuildingDescription;

	FName GoodName;
};
