#pragma once
#include "Actions/Description/Condition.h"
#include "Actions/Description/CountriesConditions.h"
#include "Actions/Description/Outcome.h"
#include "Engine/DataTable.h"
#include "LawDescription.generated.h"



UCLASS()
class ULawDescription: public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	FText Description;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FCondition> Conditions;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FOutcome> Outcomes;
};
