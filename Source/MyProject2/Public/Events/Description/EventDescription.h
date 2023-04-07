#pragma once
#include "EventChoice.h"
#include "Actions/Description/Condition.h"
#include "Actions/Description/CountriesConditions.h"
#include "Engine/DataTable.h"
#include "EventDescription.generated.h"

UCLASS()
class UEventDescription: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Image;

	UPROPERTY(EditDefaultsOnly)
	FText Title;

	UPROPERTY(EditDefaultsOnly)
	FText Text;

	UPROPERTY(EditDefaultsOnly)
	bool TriggerOnce;
	
	UPROPERTY(EditDefaultsOnly)
	FCountriesConditions CountriesConditions;

	UPROPERTY(EditDefaultsOnly)
	TArray<FCondition> Conditions;

	UPROPERTY(EditDefaultsOnly)
	TArray<FEventChoice> Choices;
};
