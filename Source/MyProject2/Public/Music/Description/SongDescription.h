#pragma once
#include "Engine/DataTable.h"
#include "SongDescription.generated.h"

UCLASS()
class USongDescription: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	FText WrittenBy;

	UPROPERTY(EditDefaultsOnly)
	FText SungBy;

	UPROPERTY(EditDefaultsOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* Song;
};
