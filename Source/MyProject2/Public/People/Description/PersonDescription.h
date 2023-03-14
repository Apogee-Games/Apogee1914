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
	FName CountryTag;
	
	UPROPERTY()
	FDateTime Age;

	UPROPERTY()
	TMap<FName, FName> Skills;

	UPROPERTY()
	TArray<FName> Professions;
};
