#pragma once
#include "Engine/DataTable.h"
#include "GoodDescription.generated.h"

USTRUCT()
struct FGoodDescription : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();
public:
	FGoodDescription();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GoodType)
	FString GoodName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GoodType)
	int32 AveragePrice;

	
};