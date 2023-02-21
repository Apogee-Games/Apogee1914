#pragma once
#include "Engine/DataTable.h"
#include "GoodDescription.generated.h"

USTRUCT()
struct FGoodDescription : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GoodType)
	FName GoodName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GoodType)
	int32 AveragePrice = 0;

	
};