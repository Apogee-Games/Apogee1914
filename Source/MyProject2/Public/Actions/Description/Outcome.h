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
	FText Description;
	
	UPROPERTY()
	TMap<FName, FString> Values;
};
