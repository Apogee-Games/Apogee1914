#pragma once
#include "Military/Descriptions/UnitDescription.h"
#include "UnitDescriptionCarrier.generated.h"

UCLASS()
class UUnitDescriptionCarrier : public UObject
{
	GENERATED_BODY()
public:
	void Init(const FUnitDescription* ProvidedUnitDescription);

	const FUnitDescription* GetUnitDescription() const;
private:
	const FUnitDescription* UnitDescription;
};
