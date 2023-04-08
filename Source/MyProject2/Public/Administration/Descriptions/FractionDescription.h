#pragma once
#include "Engine/DataTable.h"
#include "FractionDescription.generated.h"

USTRUCT()
struct FFractionDescription: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	FName IdeologyTag;
	
	UPROPERTY(EditDefaultsOnly)
	FText FractionName;

	UPROPERTY(EditDefaultsOnly)
	int32 MembersNumber;
};
