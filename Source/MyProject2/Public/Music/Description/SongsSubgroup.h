#pragma once
#include "SongDescription.h"
#include "SongsSubgroup.generated.h"

UCLASS()
class USongsSubgroup: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<USongDescription*> Songs;

	UPROPERTY(EditDefaultsOnly)
	FText Name;
};
