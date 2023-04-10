#pragma once
#include "SongsSubgroup.h"
#include "SongsGroup.generated.h"

UCLASS()
class USongsGroup: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<USongsSubgroup*> Subgroups;

	UPROPERTY(EditDefaultsOnly)
	FText Name;
};
