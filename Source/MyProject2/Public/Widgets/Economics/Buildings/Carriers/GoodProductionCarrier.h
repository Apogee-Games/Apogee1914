#pragma once
#include "Blueprint/UserWidget.h"
#include "Economics/Description/BuildingDescription.h"

#include "GoodProductionCarrier.generated.h"

UCLASS()
class UGoodProductionCarrier: public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(const FBuildingDescription* ProvidedBuildingDescription, const FName& ProvidedGoodName);

	const FName& GetGoodName() const;

	int32 GetGoodProduction() const;
		
private:
	const FBuildingDescription* BuildingDescription;

	FName GoodName;
};
