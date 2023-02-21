#pragma once
#include "Engine/DataTable.h"
#include "EventOutcome.generated.h"

USTRUCT()
struct FEventOutcome : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY()
	FName Name;

	UPROPERTY()
	TMap<FName, FString> Values;
};
