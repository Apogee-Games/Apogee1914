#pragma once
#include "Engine/DataTable.h"
#include "PersonDescription.generated.h"

USTRUCT()
struct FPersonDescription: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName ImagePath;
	
	UPROPERTY()
	FName PersonName;
	
	UPROPERTY()
	int32 Age;

	UPROPERTY()
	TMap<FName, FName> Skills;

	UPROPERTY()
	TArray<FName> Professions;
};
