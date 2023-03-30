#pragma once
#include "Engine/DataTable.h"
#include "Condition.generated.h"

USTRUCT()
struct FCondition: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName Name;
	
	UPROPERTY()
	FText Description;
	
	UPROPERTY()
	TMap<FName, FString> Values;
};
