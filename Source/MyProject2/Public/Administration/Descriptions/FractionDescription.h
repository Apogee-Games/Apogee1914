#pragma once
#include "Engine/DataTable.h"
#include "FractionDescription.generated.h"

USTRUCT()
struct FFractionDescription: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY()
	FName IdeologyTag;
	
	UPROPERTY()
	FText FractionName;

	UPROPERTY()
	int32 MembersNumber;
};
