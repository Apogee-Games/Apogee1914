﻿#pragma once
#include "Engine/DataTable.h"

USTRUCT()
struct FFactoryInstance : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FString Type; // FactoryDescriptionId

	UPROPERTY()
	int Labours; // Current amount of labours
 	
	
};
