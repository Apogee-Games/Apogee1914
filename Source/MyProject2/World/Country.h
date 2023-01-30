#pragma once
#include "Engine/DataTable.h"
#include "Country.generated.h"


USTRUCT(BlueprintType)
struct FCountry : public FTableRowBase
{
	GENERATED_BODY()	
public:
	FCountry();

	FCountry(const FString& Tag, const FColor& Color);
	
	FString GetTag() const;

	FColor GetColor() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Tag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FColor Color;
};
