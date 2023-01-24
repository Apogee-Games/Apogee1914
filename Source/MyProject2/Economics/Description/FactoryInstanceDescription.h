#pragma once
#include "Engine/DataTable.h"
#include "FactoryInstanceDescription.generated.h"

USTRUCT()
struct FFactoryInstanceDescription : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FString Type; // FactoryDescriptionId

	UPROPERTY()
	int Labours; // Current amount of labours
 	
	
};
