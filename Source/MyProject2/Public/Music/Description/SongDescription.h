#pragma once
#include "Engine/DataTable.h"
#include "SongDescription.generated.h"

USTRUCT()
struct FSongDescription: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY()
	FText SongName;

	UPROPERTY()
	FText WrittenBy;

	UPROPERTY()
	FText SungBy;

	UPROPERTY()
	FText Description;

	UPROPERTY()
	FString Path;

	UPROPERTY()
	FName Group;

	UPROPERTY()
	FName Subgroup;
};
