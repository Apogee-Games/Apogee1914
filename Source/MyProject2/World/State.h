#pragma once
#include "Engine/DataTable.h"
#include "State.generated.h"

USTRUCT()
struct FState : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString StateName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> Provinces;
};
