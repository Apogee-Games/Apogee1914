#pragma once
#include "StateDescription.generated.h"

class UProvinceDescription;

UCLASS()
class UStateDescription: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly)
	TArray<UProvinceDescription*> Provinces;
};
