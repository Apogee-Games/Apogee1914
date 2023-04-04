#pragma once

#include "ResourceDescription.generated.h"

UCLASS()
class UResourceDescription: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FName Name;
	
	UPROPERTY(EditDefaultsOnly)
	FText NameText;

	UPROPERTY(EditDefaultsOnly)
	FText Description;
};
