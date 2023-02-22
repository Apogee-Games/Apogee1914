#pragma once
#include "Engine/DataTable.h"
#include "ResourceDescription.generated.h"

USTRUCT()
struct FResourceDescription: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FString ResourceName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;
};
