#pragma once
#include "MyProject2/Military/Descriptions/UnitDescription.h"

#include "GoodRequirementCarrier.generated.h"

UCLASS()
class UGoodRequirementCarrier: public UObject
{
	GENERATED_BODY()
public:
	void Init(const FUnitDescription* ProvidedUnitDescription, const FName& ProvidedGoodName);

	int32 GetRequirement() const;

	const FName& GetGoodName() const;
private:
	const FUnitDescription* UnitDescription;
	
	const FName* GoodName;
};
