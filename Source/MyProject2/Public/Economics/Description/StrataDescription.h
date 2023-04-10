#pragma once
#include "StrataDescription.generated.h"

UCLASS()
class UStrataDescription : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;
};
