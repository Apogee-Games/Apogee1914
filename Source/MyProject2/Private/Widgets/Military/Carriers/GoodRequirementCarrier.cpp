
#include "Widgets/Military/Carriers/GoodRequirementCarrier.h"

void UGoodRequirementCarrier::Init(const FUnitDescription* ProvidedUnitDescription, const FName& ProvidedGoodName)
{
	UnitDescription = ProvidedUnitDescription;
	GoodName = &ProvidedGoodName;
}

int32 UGoodRequirementCarrier::GetRequirement() const
{
	return UnitDescription->EquipmentRequirements[*GoodName];
}

const FName& UGoodRequirementCarrier::GetGoodName() const
{
	return *GoodName;
}
