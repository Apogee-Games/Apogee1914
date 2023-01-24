#pragma once
#include "Engine/DataTable.h"
#include "EventCondition.generated.h"

USTRUCT()
struct  FEventCondition: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FString Name;
	
	UPROPERTY()
	TMap<FString, FString> Values;
};
