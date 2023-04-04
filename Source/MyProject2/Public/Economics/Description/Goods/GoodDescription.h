#pragma once
#include "Engine/DataTable.h"
#include "GoodDescription.generated.h"

USTRUCT()
struct FGoodDescription : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	FName GoodName;
	
	UPROPERTY(EditDefaultsOnly)
	int32 AveragePrice = 0;
};