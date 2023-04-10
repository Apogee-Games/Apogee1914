#pragma once
#include "Engine/DataTable.h"
#include "Condition.generated.h"

USTRUCT()
struct FCondition: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName Name;
	
	UPROPERTY(EditDefaultsOnly)
	FText Description;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FString> Values;
};
