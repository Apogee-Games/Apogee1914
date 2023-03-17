#pragma once
#include "Engine/DataTable.h"
#include "Outcome.generated.h"

USTRUCT()
struct FOutcome : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY()
	FName Name;

	UPROPERTY()
	TMap<FName, FString> Values;
};
