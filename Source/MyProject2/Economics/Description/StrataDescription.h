#pragma once
#include "Engine/DataTable.h"
#include "StrataDescription.generated.h"

USTRUCT()
struct FStrataDescription : public FTableRowBase
{
	GENERATED_BODY()
public:
	FStrataDescription()
	{
		StrataName = "NULL_STRATA_NAME";
	};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString StrataName;
	
};
