#pragma once
#include "Engine/DataTable.h"
#include "Resource.generated.h"

USTRUCT()
struct FResource: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;
};
