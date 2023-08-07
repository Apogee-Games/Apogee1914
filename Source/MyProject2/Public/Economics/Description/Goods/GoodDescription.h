#pragma once
#include "Engine/DataAsset.h"
#include "GoodDescription.generated.h"

UCLASS(Abstract)
class UGoodDescription : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly)
	FText NameText;
	
	UPROPERTY(EditDefaultsOnly)
	FText Description;
	
	UPROPERTY(EditDefaultsOnly)
	int32 AveragePrice = 0;

	UPROPERTY(EditDefaultsOnly)
	FName Group;

	UPROPERTY(EditDefaultsOnly)
	FName Subgroup;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Image;
};