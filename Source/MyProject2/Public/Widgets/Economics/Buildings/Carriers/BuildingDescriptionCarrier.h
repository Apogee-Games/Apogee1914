#pragma once
#include "Economics/Description/BuildingDescription.h"

#include "BuildingDescriptionCarrier.generated.h"

UCLASS()
class UBuildingDescriptionCarrier: public UObject
{
	GENERATED_BODY()
public:
	void Init(const FBuildingDescription* ProvidedBuildingDescription);

	const FBuildingDescription* GetBuildingDescription() const;
	
private:
	const FBuildingDescription* BuildingDescription; 	
};
