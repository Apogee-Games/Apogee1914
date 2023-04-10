#pragma once
#include "Military/Descriptions/UnitDescription.h"

#include "GoodRequirementCarrier.generated.h"

UCLASS()
class UGoodRequirementCarrier: public UObject
{
	GENERATED_BODY()
public:
	void Init(UUnitDescription* ProvidedUnitDescription, UGoodDescription* ProvidedGood);

	int32 GetRequirement() const;

	const FText& GetGoodName() const;
private:
	UPROPERTY()
	UUnitDescription* UnitDescription;
	
	UPROPERTY()
	UGoodDescription* Good;
};
