#pragma once
#include "Engine/DataTable.h"
#include "EventCondition.generated.h"

USTRUCT()
struct  FEventCondition: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName Name;
	
	UPROPERTY()
	TMap<FName, FString> Values;
};
