#pragma once
#include "Engine/DataTable.h"
#include "ResourceDescription.generated.h"

USTRUCT()
struct FResourceDescription: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName ResourceName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;
};
