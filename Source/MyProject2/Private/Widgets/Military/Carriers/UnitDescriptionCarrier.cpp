
#include "Widgets/Military/Carriers/UnitDescriptionCarrier.h"

void UUnitDescriptionCarrier::Init(const FUnitDescription* ProvidedUnitDescription)
{
	UnitDescription = ProvidedUnitDescription;
}

const FUnitDescription* UUnitDescriptionCarrier::GetUnitDescription() const
{
	return UnitDescription;
}
