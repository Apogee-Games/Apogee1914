#pragma once
#include "Engine/DataTable.h"
#include "Outcome.generated.h"

USTRUCT()
struct FOutcome : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly)
	FText Description;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FString> Values;
};
