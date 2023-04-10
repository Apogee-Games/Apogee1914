#pragma once
#include "IdeologyDescription.generated.h"

UCLASS()
class UIdeologyDescription: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	FColor Color;
};
