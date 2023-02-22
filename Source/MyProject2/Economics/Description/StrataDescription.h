﻿#pragma once
#include "Engine/DataTable.h"
#include "StrataDescription.generated.h"

USTRUCT()
struct FStrataDescription : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName StrataName;
	
};
