#pragma once
#include "Engine/DataTable.h"
#include "FactoryInstanceDescription.generated.h"

USTRUCT()
struct FFactoryInstanceDescription : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FName Type; 

	UPROPERTY()
	int32 Labours;
};
