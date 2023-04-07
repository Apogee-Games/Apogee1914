#pragma once
#include "LawDescription.h"
#include "LawsSubgroup.generated.h"

UCLASS()
class ULawsSubgroup: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	TArray<ULawDescription*> Laws;
};
